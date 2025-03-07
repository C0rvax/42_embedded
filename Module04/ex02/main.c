#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t counter = 0;

void update_leds()
{
    PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))) | ((counter & 0x07) | ((counter & 0x08) << 1));
}

int main(void)
{
    // set led to out (1)
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);

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

ISR(INT0_vect) // interrupt on INT0 (PD2)
{
    _delay_ms(50); // Anti-rebond
    if (counter < 15)
        counter++;
    update_leds();
}

ISR(PCINT2_vect) // interrupt on PCINT2 (PD4)
{
    _delay_ms(50); // Anti-rebond
    if (counter > 0)
        counter--;
    update_leds();
}
