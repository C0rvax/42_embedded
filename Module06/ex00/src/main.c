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
	i2c_start();
	uart_tx_string("i2c Started :");
	uart_print_status(TWSR);
	uart_tx_string("\r\n");
	i2c_write();
	uart_tx_string("i2c Write :");
	uart_print_status(TWSR);
	uart_tx_string("\r\n");
	i2c_stop();
	uart_tx_string("i2c Stop :");
	uart_print_status(TWSR);
	uart_tx_string("\r\n");
	i2c_start();
	uart_tx_string("i2c Started :");
	uart_print_status(TWSR);
	uart_tx_string("\r\n");
	i2c_write();
	uart_tx_string("i2c Write :");
	uart_print_status(TWSR);
	uart_tx_string("\r\n");
	i2c_stop();
	uart_tx_string("i2c Stop :");
	uart_print_status(TWSR);
	uart_tx_string("\r\n");
	/*
	while (1)
	{
		i2c_start();
		i2c_write();
		i2c_stop();
	}
	*/
}

