#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void	init_setup(void)
{
	DDRB |= (1 << PB0); // D1 LED out (1)
	DDRD &= ~(1 << PD2); // D1 LED in (0)
	PORTD |= (1 << PD2); // pull-up resistor
	
	EICRA |= (1 << ISC01); // falling edge on sw1
	EIMSK |= (1 << INT0);
	sei();
}

ISR(INT0_vect)
{
	EIMSK &= ~(1 << INT0); // disable interruption
	_delay_ms(50);
	PORTB ^= (1 << PB0);
	EIMSK |= (1 << INT0); // enable interruption
}

int	main(void)
{
	init_setup();
	while (1);
}
