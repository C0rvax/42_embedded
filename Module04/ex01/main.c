#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define TMAX 30

volatile uint8_t cycle = 0;
volatile int8_t step = 1;

void	init_timers(void)
{
	// Config Timer0
	TCCR0A = 0; // Normal Mode
	TCCR0B |= (1 << CS00) | (1 << CS02); // Prescaler 1024
	TIMSK0 |= (1 << TOIE0); // overflow interrupt every 1024 (Prescaler) * 256 (TOP 0xFF) ticks (61 in a sec)


	// Config Timer1
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // PWM Phase correct TOP ICR1 clear on compare set on TOP
	TCCR1B |= (1 << WGM10) | (1 << WGM13)| (1 << CS10); // Prescaler 1
	ICR1 = TMAX;
	OCR1A = cycle;

	sei();
}

ISR(TIMER0_OVF_vect)
{

	cycle += step;
	if (cycle == TMAX || cycle == 0)
		step = -step; // reverse step
	OCR1A = cycle;
}

int	main(void)
{
	DDRB |= (1 << PB1);
	init_timers();
	while (1);
}
