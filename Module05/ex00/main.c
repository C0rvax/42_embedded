#include "prog.h"
#include <avr/io.h>
#include <util/delay.h>

void adc_init(void)
{
    // Select the reference voltage AVCC and the ADC0 channel (potentiometer)
    ADMUX = (1 << REFS0) | (1 << ADLAR); // AVCC as reference, 8-bit (ADLAR = left) (see section 23.9.1 p.217)
	// MUX3..0 = 0 (ADC0) (p.218)
    
    // Enable the ADC, prescale by 128 for good accuracy (~125kHz at 16MHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // (see section 24.9.2 of the doc)
}

// Function to read the ADC (8 bits)
uint8_t adc_read(void)
{
    ADCSRA |= (1 << ADSC); // Start the conversion (see section 24.9.2 of the doc)
    while (ADCSRA & (1 << ADSC)); // Wait for the conversion to finish
    return ADCH; // Return the 8-bit value
}

// Function to transmit a value in hexadecimal
void print_hex(uint8_t value)
{
    // Convert the value to hexadecimal (2 hex digits)
    char high = (value >> 4) & 0x0F; // Get the high 4 bits
    char low = value & 0x0F; // Get the low 4 bits

    // Convert the values to hex characters (0-9, A-F)
    if (high < 10)
        uart_tx(high + '0'); // If between 0 and 9, display the digit
    else
        uart_tx(high - 10 + 'A'); // If between A and F, display the letter

    if (low < 10)
        uart_tx(low + '0'); // Same for the low part
    else
        uart_tx(low - 10 + 'A');

    uart_tx_string("\r\n"); // New line after the value
}

int main(void)
{
    adc_init(); // Init ADC
	uart_init(); // Init UART
    while (1)
	{
        uint8_t adc_value = adc_read(); // Read the value from the potentiometer
        print_hex(adc_value); // Display the value in hexadecimal
        _delay_ms(20); // Wait 20ms
    }

    return 0;
}

