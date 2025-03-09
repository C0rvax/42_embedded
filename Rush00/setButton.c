#include "init.h"

void	init_led(void)
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
}

void	init_but(void)
{
    // Config PD2 (SW1) and PD4 (SW2) to in (0) with pull-up res
    DDRD &= ~((1 << PD2) | (1 << PD4));
    PORTD |= (1 << PD2) | (1 << PD4);
	
    // Configure INT0 on falling edge
    EICRA |= (1 << ISC01); // INT0 (PD2)
    EIMSK |= (1 << INT0); // Activate INT0
	
    // Configure PCINT2 on falling edge
	PCICR |= (1 << PCIE2); // PCINT2 (PD4)
	PCMSK2 |= (1 << PCINT20); // Activate PCINT2
	sei();
}

ISR(INT0_vect) // interrupt on INT0 (PD2)
{
	if (!master)
		init_master();
}

ISR(PCINT2_vect) // interrupt on PCINT2 (PD4)
{
	if (master && started)
		winMaster();
	else if (!master && started)
		winSlave();
	else if (master && !started)
		start_master();
	else
		start_slave();
}
