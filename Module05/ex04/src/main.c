#include "adc.h"
#include "led.h"
#include <util/delay.h>

 /*
 * LDR Light Dependent Resistor -> res go down when light go up
 * NTC Negative Temperature Coefficient -> res go down when heat go up
 */

int main(void)
{
    adc_init(); // Init ADC
	init_rgb();
	init_led();
	uint8_t rv1;
    while (1)
	{
		rv1 = adc_read(0);
		wheel(rv1);
		set_led(rv1);
        _delay_ms(20); // Wait 20ms
    }
}

