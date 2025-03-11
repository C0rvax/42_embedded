#include "i2c.h"
#include "prog.h"
#include <util/twi.h>

void	i2c_init(void)
{
	TWSR = 0; // prescaler 1
	TWBR = (uint8_t)TWBR_VALUE;
}

void	i2c_write( uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void	i2c_start(void)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));

	uart_tx_string("i2c Started :");
	uart_print_status(TWSR & 0xF8);
	uart_tx_string("\r\n");

	i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
	uart_tx_string("i2c addr :");
	uart_print_status(TWSR & 0xF8);
	uart_tx_string("\r\n");
}

void	i2c_stop(void)
{
	TWSR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));

	uart_tx_string("i2c Stop :");
	uart_print_status(TWSR & 0xF8);
	uart_tx_string("\r\n");
}

