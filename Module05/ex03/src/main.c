#include "prog.h"
#include "adc.h"
#include <stdint.h>
#include <util/delay.h>

#define TS_GAIN 100
#define TS_OFFSET 0
 /*
 * LDR Light Dependent Resistor -> res go down when light go up
 * NTC Negative Temperature Coefficient -> res go down when heat go up
 */

uint16_t	convert_to_c(uint16_t value)
{
	int32_t temperature = (((value - 373 - TS_OFFSET) * 128) / TS_GAIN) + 25;
	return (uint16_t)temperature;
}

int main(void)
{
    adc_init(); // Init ADC
	uart_init(); // Init UART
	char tmp[5];
    while (1)
	{
		uint16_t temperature = convert_to_c(adc_read());
		uint16_to_str(temperature, tmp);
		uart_tx_string(tmp);
		uart_tx_string("\r\n");
        _delay_ms(20); // Wait 20ms
    }
}

