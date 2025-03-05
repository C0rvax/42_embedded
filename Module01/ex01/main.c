#include <avr/io.h>

// TCCRx Timer/Counter Control Register
// WGM Waveform Generator Mode
// CS Clock Select
// OCRx Output Compare Register
// TCNTx Timer/Counter
// COMx Compare Output Mode
// 1s = 16000000 / 256 (prescaler) = 62500
int	main()
{
	/*
	DDRB |= (1 << PB1); // set PB1 to out (1)

	TCCR1B |= (1 << WGM12); // Mode CTC (Clear Timer on Compare Match) (page 109)
	TCCR1B |= (1 << CS12) | (1 << CS10); // with a prescaler of 1024 (page 110)
	TCCR1A |= (1 << COM1A0); // define toggle mode on OC1A (page 108)
	
	OCR1A = 7812; // comparare value for 500ms (16000000 / 1024 / 2)
*/	
	DDRB |= (1 << PB1); // set PB1 to out (1)
	TCCR1B |= (1 << WGM13); // mode 10 PWM phase correct ICR1 TOP
	TCCR1A |= (1 << WGM11); // mode 10 PWM phase correct ICR1 TOP
	TCCR1B |= (1 << CS12); // with a prescaler of 256 (page 110)
	TCCR1A |= (1 << COM1A1); // clear at match up-counting / set down-couting
	OCR1A = 62500 / 4;
	ICR1 = 62500 / 2;
	while (1);
	return 0;
}
