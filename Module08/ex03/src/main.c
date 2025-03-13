#include "spi.h"

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();

    while (1)
    {
        // Turn on LED D6 connected to MOSI (PB3)
        _delay_ms(250);
		APA102(0, 31, 255, 255, 255);
        _delay_ms(250);
		APA102(1, 31, 255, 255, 255);
        _delay_ms(250);
		APA102(2, 31, 255, 255, 255);
        _delay_ms(250);
		APA102(4, 31, 0, 0, 0);
        _delay_ms(250);
    }
}
