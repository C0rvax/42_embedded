#include <avr/io.h>

int	main()
{

	DDRB |= (1 << PB0); // set PB0 (port B, pin 0) to out (1)
	DDRD &= ~(1 << PD2); // set PD2 to in (0)
	PORTD |= (1 << PD2); // set PD2 pull-up res to high (1)

	// PINX (Input Pins Register) read the state of pin (in only)
	while (1)
	{
		if (PIND & (1 << PD2)) // if PD2 is high (button released)
			PORTB &= ~(1 << PB0); // shut off PB0
		else
		 PORTB |= (1 << PB0);
	}
	return 0;
}
