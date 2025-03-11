#include "adc.h"
#include <stdint.h>

/*
* ADMUX ADC Multiplexer Selection Register
* ADCSRA ADC Constrol and Status Register A
* ADSC ASC Start Conversion
*/

// Function init ADC 8-bit (ADLAR) AVCC with external capacitor
void adc_init(void)
{
    // Select the reference voltage AVCC
    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);; // channel ADC8 intern temp (p.218)
    
    // Enable the ADC, prescale by 128 for good accuracy (~125kHz at 16MHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // (see section 24.9.2 of the doc)
}

// Function to read the ADC (8 bits)
uint16_t adc_read(void)
{
    ADCSRA |= (1 << ADSC); // Start the conversion (see section 24.9.2 of the doc)
    while (ADCSRA & (1 << ADSC)); // Wait for the conversion to finish
    return ADC; // Return the 8-bit value (no 2 bits in ADCL)
}

// Function to convert a value in decimal char*
void	uint16_to_str(uint16_t value, char* dec_str)
{
	uint8_t i = 0;
	char	tmp[5];
	if (value == 0)
		dec_str[i++] = '0';
	else
	{
		while (value > 0)
		{
			tmp[i++] = (value % 10) + '0';
			value /= 10;
		}
		for (uint8_t j = 0; j < i; j++)
			dec_str[j] = tmp[i - j - 1];
	}
	dec_str[i] = '\0';
}
