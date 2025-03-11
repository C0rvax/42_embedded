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
}

void	i2c_stop(void)
{
	TWSR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void	i2c_write(void)
{
	TWDR = AH20_ADDRESS << 1 | TW_WRITE;
	while (!(TWCR & (1 << TWINT)));
}
