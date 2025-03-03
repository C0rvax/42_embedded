#include <avr/io.h>
#include <avr/interrupt.h>

int	main()
{
	DDRB |= (1 << PB1); // set PB1 to out (1)

	TCCR1B |= (1 << WGM12); // Mode CTC (Clear Timer on Compare Match) (page 109)
	TCCR1B |= (1 << CS12) | (1 << CS10); // with a prescaler of 1024 (page 110)
	
	OCR1A = 7812; // comparare value for 500ms (16000000 / 1024 * 0.5)
	
	TIMSK1 |= (1 << OCIE1A); // activate interrupt for OCR1A (TIMSK1 -> timer interrupt mask register) (page 97 and 112)
	
	asm ("SEI"); // activate global interrupt (page 283)
//	sei(); // activate global interrupt
	while (1);
	return 0;
}

ISR(TIMER1_COMPA_vect) // (interrupt Service Routine) interrupt routine for the interrupt vector Timer1 Compare Match A
{
	PINB |= (1 << PB1); // reverse PB1 only for pin set in out mode
}
