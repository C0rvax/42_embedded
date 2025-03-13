#include "spi.h"
#include "adc.h"
#include "i2c.h"

#define SW2_PIN PIND4
#define SW3_I2C_ADDRESS 0x20 // Example I2C address for the expander
#define SW3_PIN 0x10 // Pin 100_0 (4) on the PCA9555PW

void init_buttons(void)
{
    DDRD &= ~(1 << SW2_PIN); // Set SW2 as input
    PORTD |= (1 << SW2_PIN); // Enable pull-up resistor for SW2
    i2c_init(); // Initialize I2C for SW3
    pca9555_init(SW3_I2C_ADDRESS); // Initialize PCA9555PW
}

uint8_t read_button(uint8_t pin)
{
    return !(PIND & (1 << pin)); // Return 1 if button is pressed
}

uint8_t read_button_i2c(uint8_t address, uint8_t pin)
{
    i2c_start();
    i2c_write(address << 1); // Write mode
    i2c_write(0x00); // Command to read the pin state
    i2c_start();
    i2c_write((address << 1) | 1); // Read mode
    uint8_t state = i2c_read(0);
    i2c_stop();
    return !(state & pin); // Return 1 if button is pressed
}

int main(void)
{
    SPI_MasterInit();
    adc_init();
    init_buttons();

    uint8_t current_led = 0; // 0: D6, 1: D7, 2: D8
    uint8_t current_color = 0; // 0: Red, 1: Green, 2: Blue
    uint8_t colors[3][3] = {0}; // Store RGB values for each LED

    while (1)
    {
        uint8_t adc_value = adc_read(0); // Read potentiometer value

        if (read_button(SW2_PIN))
        {
            colors[current_led][current_color] = adc_value; // Set current color value
            current_color = (current_color + 1) % 3; // Move to next color
            _delay_ms(200); // Debounce delay
        }

        if (read_button_i2c(SW3_I2C_ADDRESS, SW3_PIN))
        {
            current_led = (current_led + 1) % 3; // Move to next LED
            _delay_ms(200); // Debounce delay
        }

        // Update LEDs
        APA102(0, BRIGHTNESS, colors[0][0], colors[0][1], colors[0][2]);
        APA102(1, BRIGHTNESS, colors[1][0], colors[1][1], colors[1][2]);
        APA102(2, BRIGHTNESS, colors[2][0], colors[2][1], colors[2][2]);
    }
}
