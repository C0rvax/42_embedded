#include <avr/io.h>

int	main()
{
	DDRB |= (1 << PB1); // set PB1 to out (1)

	// configure Timer1 in mode Fast PWM (Mode 14) with ICR1 for TOP
	TCCR1A |= (1 << COM1A1); // Mode PWM, OC1A "Clear on compare Match" (page 109)
	TCCR1A |= (1 << WGM11); // Mode Fast PWM with ICR1 TOP and OCR1A at BOTTOM (mode 14, page 109)
	TCCR1B |= (1 << WGM12) | (1 << WGM13); // Mode Fast PWM with ICR1 and OCR1A at BOTTOM (mode 14, page 109)
	TCCR1B |= (1 << CS12) | (1 << CS10); // with a prescaler of 1024 (page 110)
	
	ICR1 = 15625; // set TOP = 1s (15625 * 1024 = 16 Hz)
	OCR1A = 1562; // set BOTTOM at 100ms (16000000 / 1024 * 0.1) for 10%
	
	return 0;
}
