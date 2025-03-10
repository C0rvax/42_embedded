#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void start_debounce_timer()
{
    // Configure Timer0 on mode CTC (Comparaison)
    TCCR0A = (1 << WGM01);  // Mode CTC
    TCCR0B = (1 << CS02) | (1 << CS00);  // Prescaler 1024
	// OCR0A + 1 = delay x F_CPU / prescaler
    OCR0A = 233;  // for delay = 15ms -> OCR0A = 0.020 * 16000000 / 1024 -1 = 232.375 
    TIMSK0 |= (1 << OCIE0A);  // Activate interrupt of Timer0 comp A
}

void	init_setup(void)
{
	DDRB |= (1 << PB0); // LED out (1)
	DDRD &= ~(1 << PD2); // Button sw1 in (0)
	PORTD |= (1 << PD2); // pull-up resistor on sw1
	
	EICRA |= (1 << ISC01); // falling edge on sw1
	EIMSK |= (1 << INT0); // activate INT0
	sei();
}

ISR(TIMER0_COMPA_vect)
{
	TIMSK0 &= ~(1 << OCIE0A); // Disable interrupt Timer0
	TCCR0B = 0; // Stop timer
	PORTB ^= (1 << PB0);
	EIMSK |= (1 << INT0); // Reset INT0
}

ISR(INT0_vect)
{
	EIMSK &= ~(1 << INT0); // Disable interrupt
	_delay_ms(50);
	start_debounce_timer();
}

int	main(void)
{
	init_setup();
	while (1);
}
