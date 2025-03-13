#include "i2c.h"
#include <avr/io.h>
#include <util/twi.h>

void	i2c_init(void)
{
	TWSR = 0; // prescaler 1
	TWBR = (uint8_t)TWBR_VALUE;
}

void	i2c_write(uint8_t data)
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
	while (!(TWCR & (1 << TWINT)));
}

uint8_t	i2c_read(uint8_t ack)
{
	if (ack)
		TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	else
		TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t	isCalibrate(void)
{
	return 1;
}

void pca9555_init(uint8_t address)
{
    i2c_start();
    i2c_write(address << 1); // Write mode
    i2c_write(0x06); // Configuration register for port 0
    i2c_write(0xFF); // Set all pins of port 0 as inputs
    i2c_write(0xFF); // Set all pins of port 1 as inputs
    i2c_stop();
}

