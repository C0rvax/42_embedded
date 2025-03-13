#include "spi.h"
#include <stdint.h>

void SPI_MasterInit(void)
{
    DDRB = (1 << PB3) | (1 << PB5) | (1 << PB2); // Set MOSI and SCK and Slave Select (p.66)
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI, Master, set clock rate fck/16
}

void SPI_MasterTransmit(uint8_t data)
{
    SPDR = data; // Start transmission
    while (!(SPSR & (1 << SPIF))); // Wait for transmission complete
}

void	APA102_send(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue)
{
	SPI_MasterTransmit(0xE0 | (brightness & 0x1F)); // Max intensity = 0b11100000
	SPI_MasterTransmit(blue);
	SPI_MasterTransmit(green);
	SPI_MasterTransmit(red);
}

void	APA102(uint8_t led, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint8_t i = 0; i < 4; i++)
		SPI_MasterTransmit(0x00); // Initialize sequence (4o to 0)
	switch (led)
	{
		case 0:
			APA102_send(brightness, red, green, blue);
			APA102_send(brightness, 0, 0, 0);
			APA102_send(brightness, 0, 0, 0);
			break;
		case 1:
			APA102_send(brightness, 0, 0, 0);
			APA102_send(brightness, red, green, blue);
			APA102_send(brightness, 0, 0, 0);
			break;
		case 2:
			APA102_send(brightness, 0, 0, 0);
			APA102_send(brightness, 0, 0, 0);
			APA102_send(brightness, red, green, blue);
			break;
		default:
			break;
	}
	for (uint8_t i = 0; i < 4; i++)
		SPI_MasterTransmit(0xFF);
}
