#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// TCCRx Timer/Counter Control Register
// WGM Waveform Generator Mode
// CS Clock Select
// OCRx Output Compare Register
// TCNTx Timer/Counter
// COMx Compare Output Mode
// EICRA External Interupt Control Register A
// EIMSK External Interupt MaSK
#define MINCYCLE 1562 // 10% of (freq/prescaler)
#define MAXCYCLE 14062 // 90% of (freq/prescaler)
#define STEP 1562

volatile uint16_t tCycle = MINCYCLE;

int	main(void)
{
	DDRB |= (1 << PB1); // set PB1 to out (1)
	DDRD &= ~((1 << PD2) | (1 << PD4)); // set PD2 and PD4 to in (1)
	PORTD |= (1 << PD2) | (1 << PD4); // set pull-up res for PD2 and PD4

	// configure Timer1 in mode Fast PWM (Mode 14) with ICR1 for TOP
	TCCR1A |= (1 << COM1A1); // Clear at OCR1A / set at BOTTOM
	TCCR1A |= (1 << WGM11); // Mode Fast PWM with ICR1 TOP (mode 14, page 109)
	TCCR1B |= (1 << WGM12) | (1 << WGM13); // Mode Fast PWM with ICR1 TOP (mode 14, page 109)
	TCCR1B |= (1 << CS12) | (1 << CS10); // with a prescaler of 1024 (page 110)
	
	ICR1 = MINCYCLE + MAXCYCLE; // set TOP = 1s (15625 * 1024 = 16 Hz)
	OCR1A = tCycle;

	EICRA |= (1 << ISC01); // falling edge generates interupt for INT0 and INT1 (page 54)
	EIMSK |= (1 << INT0); // enable INT0 (p.55)
 
	PCICR |= (1 << PCIE2); // activate PCINT[23:16] (PD4)
	PCMSK2 |= (1 << PCINT20); // enable change with PD4
	sei(); // set the I-bit of Status Register (SREG) at 1 (p.11 and 16) -> Global Interupt Enable
	while (1);
	return 0;
}

ISR(INT0_vect) // (Interupt Service Routine) vector (p.49)
{
	_delay_ms(40);
	if (tCycle <= MAXCYCLE)
		tCycle += STEP;
	OCR1A = tCycle;
}

ISR(PCINT2_vect)
{
	_delay_ms(40);
	if (tCycle >= MINCYCLE)
		tCycle -= STEP;
	OCR1A = tCycle;
}
