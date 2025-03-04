#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

volatile uint8_t value = 0;

int	main()
{

	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4); // set PB (port B, pin 0,1,2,4) to out (1)
	DDRD &= ~((1 << PD2) | (1 << PD4)); // set PD2 and PD3 to in (0)
	PORTD |= (1 << PD2) | (1 << PD4); // set PD2 and PD3 pull-up res to high (1)

	uint8_t prevSw1State = 1;
	uint8_t prevSw2State = 1;

	while (1)
	{
		uint8_t sw1State = PIND & (1 << PD2);
		uint8_t sw2State = PIND & (1 << PD4);

		if (!(sw1State) && prevSw1State)
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD2)))
			{
				value++;
				if (value > 15) value = 0;
				PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))) | ((value & 0x07) | ((value & 0x08) << 1));
			}
		}
		if (!(sw2State) && prevSw2State)
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD4)))
			{
				value--;
				if (value > 15) value = 15;
				PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))) | ((value & 0x07) | ((value & 0x08) << 1));
			}
		}
		prevSw1State = sw1State;
		prevSw2State = sw2State;
	}
	return 0;
}
