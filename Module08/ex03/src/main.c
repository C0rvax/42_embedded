#include "spi.h"
#include "adc.h"

void	set_led(uint8_t rv1)
{
	switch (rv1 / 85)
	{
		case 3:
			APA102(2, 31, 255, 255, 255);
		case 2:
			APA102(1, 31, 255, 255, 255);
		case 1:
			APA102(0, 31, 255, 255, 255);
			break;
		case 0:
			APA102(4, 31, 255, 255, 255);
	}
}

int main(void)
{
    // Initialize SPI as master
    SPI_MasterInit();
	adc_init();
	uint8_t rv1;

    while (1)
    {
		rv1 = adc_read(0);
		set_led(rv1);
        // Turn on LED D6 connected to MOSI (PB3)
    }
}
