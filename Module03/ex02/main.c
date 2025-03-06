#include <avr/io.h>
#include <util/delay.h>

void	init_rgb(void)
{
	DDRD |= (1 << PD6) | (1 << PD5) | (1 << PD3);  // PD3 (OC2B - blue), PD6 (OC0A - red), PD5 (OC0B - green)

	// Initialize timers in mode Fast PWM
	// Timer 0 for red  and green
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	TCCR0B = (1 << CS01);  // Prescaler 8

	// Timer 2 for blue
	TCCR2A = (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
	TCCR2B = (1 << CS21);  // Prescaler 8
}

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	OCR0A = r;  // Red
	OCR0B = g;  // Green
	OCR2B = b;  // Blue
}

void	wheel(uint8_t pos)
{
	pos = 255 - pos;
	if (pos < 85)
		set_rgb(255 - pos * 3, 0, pos * 3);
	else if (pos < 170)
	{
		pos -= 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	}
	else
	{
		pos -= 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}

int	main(void)
{
	init_rgb();

	while (1)
	{
		for (uint8_t i = 0; i < 255; i++)
		{
			wheel(i);
			_delay_ms(20);
		}
	}
	return 0;
}

