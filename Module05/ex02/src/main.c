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
	char tmp[5];
    while (1)
	{
		for (uint8_t i = 0; i < 3; ++i)
		{
			uint16_to_str(adc_read(i), tmp);
			uart_tx_string(tmp);
			if (i < 2)
				uart_tx(',');
			else
				uart_tx_string("\r\n"); // New line after the value
		}
        _delay_ms(20); // Wait 20ms
    }
}

