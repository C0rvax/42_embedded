#include "prog.h"
#include "i2c.h"
#include <util/delay.h>

 /*
 * LDR Light Dependent Resistor -> res go down when light go up
 * NTC Negative Temperature Coefficient -> res go down when heat go up
 */

int main(void)
{
	uart_init(); // Init UART
	i2c_init();
	while (1)
	{
		i2c_start();
		i2c_stop();
	}
}

