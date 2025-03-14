#include "spi.h"
#include "adc.h"
#include "i2c.h"
//#include "prog.h"

#define SW3_PIN 0 // Pin 100_0 (4) on the PCA9555PW

void init_buttons(void)
{
    DDRD &= ~(1 << PD4); // Set SW2 as input
    PORTD |= (1 << PD4); // Enable pull-up resistor for SW2
    i2c_init(); // Initialize I2C for SW3
    pca9555_write(PCA9555_CONFIG_PORT0, (1 << SW3_PIN));
}

uint8_t read_button(uint8_t pin)
{
    return !(PIND & (1 << pin)); // Return 1 if button is pressed
}

uint8_t read_button_i2c(uint8_t address, uint8_t pin)
{
    i2c_start();
    i2c_write(address << 1); // Write mode
    i2c_write(PCA9555_INTPUT_PORT0); // Command to read the pin state
    i2c_start();
    i2c_write((address << 1) | 1); // Read mode
    uint8_t state = i2c_read(0);
    i2c_stop();
    return !(state & (1 << pin)); // Return 1 if button is pressed
}

void	set_rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t led)
{
	APA102(led, BRIGHTNESS, r, g, b);
}

void	wheel(uint8_t pos, uint8_t led)
{
	pos = 255 - pos;
	if (pos < 85)
		set_rgb(255 - pos * 3, 0, pos * 3, led);
	else if (pos < 170)
	{
		pos -= 85;
		set_rgb(0, pos * 3, 255 - pos * 3, led);
	}
	else
	{
		pos -= 170;
		set_rgb(pos * 3, 255 - pos * 3, 0, led);
	}
}

int main(void)
{
    SPI_MasterInit();
    adc_init();
//	uart_init();
    init_buttons();

    uint8_t current_led = 0; // 0: D6, 1: D7, 2: D8
	uint8_t rv1 = adc_read(0);

    while (1)
    {
        if (read_button(PD4))
        {
			rv1 = adc_read(0);
            _delay_ms(200); // Debounce delay
        }
        if (read_button_i2c(I2C_ADDR, SW3_PIN))
        {
            current_led = (current_led + 1) % 3; // Move to next LED
            _delay_ms(200); // Debounce delay
        }
		wheel(rv1, current_led);
    }
}
