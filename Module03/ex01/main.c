#include <avr/io.h>
#include <util/delay.h>

#define BL PD3
#define GR PD6
#define RE PD5

void	init_led(void)
{
	DDRD |= (1 << RE) | (1 << GR) | (1 << BL);
}

void	set_color(uint8_t r, uint8_t g, uint8_t b)
{
	if (r) PORTD |= (1 << RE); else PORTD &= ~(1 << RE);
	if (g) PORTD |= (1 << GR); else PORTD &= ~(1 << GR);
	if (b) PORTD |= (1 << BL); else PORTD &= ~(1 << BL);
}

int	main(void)
{
	init_led();

	while (1)
	{
		set_color(1, 0, 0);
		_delay_ms(1000);
		set_color(0, 1, 0);
		_delay_ms(1000);
		set_color(0, 0, 1);
		_delay_ms(1000);
		set_color(1, 1, 0);
		_delay_ms(1000);
		set_color(0, 1, 1);
		_delay_ms(1000);
		set_color(1, 0, 1);
		_delay_ms(1000);
		set_color(1, 1, 1);
		_delay_ms(1000);
	}
	return 0;
}
