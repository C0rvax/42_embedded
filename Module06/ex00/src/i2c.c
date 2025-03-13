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
}

void	i2c_stop(void)
{
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	while (TWCR & (1 << TWSTO));
}

void	i2c_write_status(const char* prompt)
{
	uart_tx_string(prompt);
	uart_print_status(TWSR & 0xF8);
//	uart_tx_string("\r\n");
}
