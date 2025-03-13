#include "spi.h"

void SPI_MasterInit(void)
{
    DDRB = (1 << PB3) | (1 << PB5) | (1 << PB2); // Set MOSI and SCK and Slave Select (p.66)
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI, Master, set clock rate fck/16
}

void SPI_MasterTransmit(unsigned char data)
{
    SPDR = data; // Start transmission
    while (!(SPSR & (1 << SPIF))); // Wait for transmission complete
}
