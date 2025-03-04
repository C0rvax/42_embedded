#include <avr/io.h>

int	main()
{
	// DDRX (Data Direction Register) define if the pin in port X is in (0) or out (1) (Direction)
	DDRB |= (1 << PB0); // set PB0 (port B, pin 0) to out (1) (1 << PB0) shift a bit of PB0 (0) (page 61)
	// PORTX (Data Register) set level logic high (1) or low (0) for out and set pull-up resistance high (1) or low (0) for in
	PORTB |= (1 << PB0); // set PBO to high (1) turn on the LED

	// PINX (Input Pins Register) read the state of pin (in only)
	while (1);
	return 0;
}
