#include "spi.h"

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();

    while (1)
    {
        // Turn on LED D6 connected to MOSI (PB3)
        SPI_MasterTransmit(0xFF); // Send 0xFF to turn on LED D6
        _delay_ms(1000);
        // Turn off LED D6
        SPI_MasterTransmit(0x00); // Send 0x00 to turn off LED D6
        _delay_ms(1000);
    }
}
