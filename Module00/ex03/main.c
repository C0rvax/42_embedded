#include <avr/io.h>
#include <util/delay.h>

int	main()
{

	DDRB |= (1 << PB0); // set PB0 (port B, pin 0) out
	DDRD &= ~(1 << PD2); // set PD2 in (0)
	PORTD |= (1 << PD2); // set PD2 pull-up res to high (1)

	uint8_t lastButtonState = 1;
	uint8_t currentButtonState;
	while (1)
	{
		currentButtonState = (PIND & (1 << PD2)) >> PD2;
		if (lastButtonState == 1 && currentButtonState == 0)
		{
			PORTB ^= (1 << PB0); // revert LED state ^= XOR
			_delay_ms(50);
		}
		lastButtonState = currentButtonState;
	}
	return 0;
}
