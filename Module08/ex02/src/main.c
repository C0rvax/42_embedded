#include "spi.h"

int main(void)
{
    SPI_MasterInit();
    while (1)
    {
		for (uint8_t i = 0; i < 3; ++i)
		{
			APA102(i, BRIGHTNESS, 255, 255, 255);
			_delay_ms(250);
		}
		APA102(4, BRIGHTNESS, 0, 0, 0);
        _delay_ms(250);
    }
}
