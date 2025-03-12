#include "prog.h"
#include "i2c.h"
#include <util/delay.h>
#include <util/twi.h>
#include "prog.h"
#include <stdlib.h>

#define MEASUREMENTS 3

float calculate_temperature(uint8_t *data)
{
    uint32_t raw_temperature = ((uint32_t)data[3] & 0x0F) << 16 | (uint32_t)data[4] << 8 | (uint32_t)data[5];
    return ((float)raw_temperature / 1048576.0) * 200.0 - 50.0; // 1048576 = 2^20 (data on 20 bits) -> res between 0 and 1 / * 200 because temp go from -50 (-50) to 150 (200) (p.9 section 6.2)
}

float calculate_humidity(uint8_t *data)
{
    uint32_t raw_humidity = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((uint32_t)data[3] >> 4); // p.9 section 6.1
    return ((float)raw_humidity / 1048576.0) * 100.0;
}

void calculate_average(float *temperature, float *humidity, uint8_t *data)
{
    static float temp_history[MEASUREMENTS] = {0};
    static float hum_history[MEASUREMENTS] = {0};
    static uint8_t index = 0;
    static uint8_t count = 0;

    temp_history[index] = calculate_temperature(data);
    hum_history[index] = calculate_humidity(data);

    index = (index + 1) % MEASUREMENTS;
    if (count < MEASUREMENTS) count++;

    float temp_sum = 0;
    float hum_sum = 0;
    for (uint8_t i = 0; i < count; i++)
    {
        temp_sum += temp_history[i];
        hum_sum += hum_history[i];
    }

    *temperature = temp_sum / count;
    *humidity = hum_sum / count;
}

int main(void)
{
    uart_init(); // Init UART
    i2c_init();

    i2c_start();
    _delay_ms(40);
    i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
    i2c_write(0xBE); // initialization cmd
    i2c_write(0x08); // initialization cmd
    i2c_write(0x00); // initialization cmd
    _delay_ms(20);
    while (1)
    {
        i2c_start();
        i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
        i2c_write(0xAC); // measurement cmd
        i2c_write(0x33); // Temperature
        i2c_write(0x00); // humidity
        _delay_ms(100); // (see datasheet p.8 section 5.3.3) (80ms)

        i2c_start();
        _delay_ms(100); // (see datasheet p.8 section 5.3.3) (80ms)
        i2c_write(AH20_ADDRESS << 1 | TW_READ);

        uint8_t data[7];
        for (uint8_t i = 0; i < 6; ++i)
            data[i] = i2c_read(1);
        data[6] = i2c_read(0);

        float temperature, humidity;
        calculate_average(&temperature, &humidity, data);

        char temp_str[10];
        char hum_str[10];

        dtostrf(temperature, 6, 1, temp_str); // dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
        dtostrf(humidity, 6, 1, hum_str);

        uart_tx_string("Temperature: ");
        uart_tx_string(temp_str);
        uart_tx_string(" °C, Humidity: ");
        uart_tx_string(hum_str);
        uart_tx_string(" %\r\n");

        _delay_ms(2000);
    }
}

