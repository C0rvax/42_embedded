#include "prog.h"
#include "adc.h"
#include <util/delay.h>

 /*
 * LDR Light Dependent Resistor -> res go down when light go up
 * NTC Negative Temperature Coefficient -> res go down when heat go up
 */

int main(void)
{
    adc_init(); // Init ADC
	uart_init(); // Init UART
    while (1)
	{
		char tmp[3];
		for (uint8_t i = 0; i < 3; ++i)
		{
			uint8_to_hex(adc_read(i), tmp);
			uart_tx_string(tmp);
			if (i < 2)
				uart_tx(',');
			else
				uart_tx_string("\r\n"); // New line after the value
		}
		/*
		char potentiometer[3], ldr[3], ntc[3];
		// Read value on sensors : potentiometer (ADC0), LDR (ADC1), NTC (ADC2)
		uint8_to_hex(adc_read(0), potentiometer);
		uint8_to_hex(adc_read(1), ldr);
		uint8_to_hex(adc_read(2), ntc);

		// Print value in hex format
		uart_tx_string(potentiometer);
		uart_tx(',');
		uart_tx_string(ldr);
		uart_tx(',');
		uart_tx_string(ntc);
		uart_tx_string("\r\n"); // New line after the value
		*/
        _delay_ms(20); // Wait 20ms
    }
}

