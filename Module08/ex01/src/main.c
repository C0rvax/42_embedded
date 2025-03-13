#include "spi.h"

int main(void)
{
    SPI_MasterInit();
    while (1)
    {
		APA102(0, BRIGHTNESS, 255, 0, 0);
        _delay_ms(1000);
		APA102(0, BRIGHTNESS, 0, 255, 0);
        _delay_ms(1000);
		APA102(0, BRIGHTNESS, 0, 0, 255);
        _delay_ms(1000);
		APA102(0, BRIGHTNESS, 255, 255, 0);
        _delay_ms(1000);
		APA102(0, BRIGHTNESS, 0, 255, 255);
        _delay_ms(1000);
		APA102(0, BRIGHTNESS, 255, 0, 255);
        _delay_ms(1000);
		APA102(0, BRIGHTNESS, 255, 255, 255);
        _delay_ms(1000);
    }
}
