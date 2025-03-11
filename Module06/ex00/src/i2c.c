#include "i2c.h"
#include "prog.h"
#include <util/twi.h>

void	i2c_init(void)
{
	TWSR = 0; // prescaler 1
	TWBR = (uint8_t)TWBR_VALUE;
}

void	i2c_start(void)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) == TW_START)
		uart_tx_string("i2c Started\r\n");
}

void	i2c_stop(void)
{
	TWSR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	uart_tx_string("i2c Stoped\r\n");
}
