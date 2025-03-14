#include "spi.h"

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();

	APA102(0, BRIGHTNESS, 255, 0, 0);
    while (1);
}
