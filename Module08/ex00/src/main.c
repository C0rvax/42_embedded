#include "spi.h"

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();

    while (1)
    {
        // Turn on LED D6 connected to MOSI (PB3)
//		APA102_send(31, 255, 0, 0); // Red LED
		APA102(0, 31, 255, 0, 0);
        _delay_ms(1000);
    }
}
