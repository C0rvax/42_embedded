#include "spi.h"

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();

    while (1)
    {
        // Turn on LED D6 connected to MOSI (PB3)
		APA102(0, BRIGHTNESS, 255, 0, 0);
        _delay_ms(1000);
    }
}
