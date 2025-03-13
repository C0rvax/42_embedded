#include "spi.h"
#include "adc.h"

void	set_led(uint8_t rv1)
{
	switch (rv1 / 85)
	{
		case 3:
			APA102(2, BRIGHTNESS, 255, 255, 255);
			//fall through
		case 2:
			APA102(1, BRIGHTNESS, 255, 255, 255);
			//fall through
		case 1:
			APA102(0, BRIGHTNESS, 255, 255, 255);
			break;
		case 0:
			APA102(4, BRIGHTNESS, 255, 255, 255);
	}
}

int main(void)
{
    SPI_MasterInit();
	adc_init();
	uint8_t rv1;

    while (1)
    {
		rv1 = adc_read(0);
		set_led(rv1);
    }
}
