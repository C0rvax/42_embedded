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
	DDRB |= (1 << PB1); // set PB1 to out (1)
	TCCR1B |= (1 << WGM13); // mode 10 PWM phase correct ICR1 TOP
	TCCR1A |= (1 << WGM11); // mode 10 PWM phase correct ICR1 TOP
	TCCR1B |= (1 << CS12); // with a prescaler of 256 (page 110)
	TCCR1A |= (1 << COM1A1); // clear at match up-counting / set down-couting
	OCR1A = 62500 / 20;
	ICR1 = 62500 / 2;
	while (1);
	/*
	DDRB |= (1 << PB1); // set PB1 to out (1)

	// configure Timer1 in mode Fast PWM (Mode 14) with ICR1 for TOP
	TCCR1A |= (1 << COM1A1); // Clear at OCR1A / set at BOTTOM
	TCCR1A |= (1 << WGM11); // Mode Fast PWM with ICR1 TOP (mode 14, page 109)
	TCCR1B |= (1 << WGM12) | (1 << WGM13); // Mode Fast PWM with ICR1 TOP (mode 14, page 109)
	TCCR1B |= (1 << CS12) | (1 << CS10); // with a prescaler of 1024 (page 110)
	
	ICR1 = 15625; // set TOP = 1s (15625 * 1024 = 16 M)
	OCR1A = 1562; // set Compare match at 100ms (10% of TOP)
	*/
	
	return 0;
}
