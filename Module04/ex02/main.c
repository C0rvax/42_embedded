#include <avr/io.h>
#include <avr/interrupt.h>

#define ALL_LED ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))

volatile uint8_t counter = 0;
volatile uint8_t debounce_flag = 0;

void update_leds()
{
    PORTB = (PORTB & ~ALL_LED) | ((counter & 0x07) | ((counter & 0x08) << 1));
}

void start_debounce_timer()
{
    // Configure Timer0 on mode CTC (Comparaison)
    TCCR0A = (1 << WGM01);  // Mode CTC
    TCCR0B = (1 << CS02) | (1 << CS00);  // Prescaler 1024
	// OCR0A + 1 = delay x F_CPU / prescaler
    OCR0A = 233;  // for delay = 15ms -> OCR0A = 0.020 * 16000000 / 1024 -1 = 232.375 
    TIMSK0 |= (1 << OCIE0A);  // Activate interrupt of Timer0 comp A
}

int main(void)
{
    // set led to out (1)
    DDRB |= ALL_LED;

    // Config PD2 (SW1) and PD4 (SW2) to in (0) with pull-up res
    DDRD &= ~((1 << PD2) | (1 << PD4));
    PORTD |= (1 << PD2) | (1 << PD4);

    // Configure INT0 on falling edge
    EICRA |= (1 << ISC01); // INT0 (PD2)
    EIMSK |= (1 << INT0); // Activate INT0

	/* Configure PCINT18 on falling edge
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT18); don't work cause PCINT18 is on PCIE2 too (not PCIE1 the code is not good)
	*/

    // Configure PCINT2 on falling edge
	PCICR |= (1 << PCIE2); // PCINT2 (PD4)
	PCMSK2 |= (1 << PCINT20); // Activate PCINT2
	
    sei(); // Activate global interrupt
    while (1);
}

ISR(INT0_vect) // Interrupt sur PD2 (SW1)
{
    if (!debounce_flag)  // Check if debouncing
    {
        debounce_flag = 1;
        EIMSK &= ~(1 << INT0);  // Disable INT0 when debounce
        start_debounce_timer();  // Start timer
    }
}

ISR(PCINT2_vect) // Interrupt sur PD4 (SW2)
{
    if (!debounce_flag)
    {
        debounce_flag = 2;
        PCICR &= ~(1 << PCIE2);  // Disable PCINT2 when debounce
        start_debounce_timer();
    }
}

ISR(TIMER0_COMPA_vect) // End of debounce (50ms)
{
    TIMSK0 &= ~(1 << OCIE0A);  // Desactivate interrupt Timer0
    TCCR0B = 0;  // stop timer

    if (debounce_flag == 1)
    {
        if (!(PIND & (1 <<PD2)) && counter < 15) // sw1 is still pushed
            counter++;
        EIMSK |= (1 << INT0); // Reset interrupt
    }
    else if (debounce_flag == 2)
    {
        if (!(PIND & (1 << PD4)) && counter > 0)
            counter--;
        PCICR |= (1 << PCIE2); // Reset interrupt
    }
    update_leds();
    debounce_flag = 0;  // Reset debounce
}

