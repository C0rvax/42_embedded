#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define TMAX 62500

volatile uint16_t cycle = 0;
volatile int8_t step = 5;

void	init_timers(void)
{
	// ** Config Timer0
	TCCR0A = 0; // Normal Mode
	TCCR0B |= (1 << CS00); // Prescaler 1
	TIMSK0 |= (1 << TOIE0); // overflow interrupt every 1 (Prescaler) * 256 (TOP 0xFF) ticks (62500 in a sec)


	DDRB |= (1 << PB1);

	sei();
}

ISR(TIMER0_OVF_vect)
{
	// ** Config Timer1
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Fast PWM TOP ICR1
	TCCR1B |= (1 << WGM12) | (1 << WGM13)| (1 << CS10); // Prescaler 1
	ICR1 = TMAX;
	OCR1A = cycle;

//	TCNT1 = 0;
	cycle += step;
	if (cycle == TMAX || cycle == 0)
		step = -step; // reverse

	OCR1A = cycle;
}

int	main(void)
{
	init_timers();
	while (1);
}
