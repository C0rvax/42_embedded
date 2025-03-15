#include "i2c.h"
#include "seven.h"
#include "adc.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t timerOk = 0;

void	init_timer(void)
{
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC prescaler 1024
	OCR1A = 15624; // 30Hz
	TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
	timerOk = 1;
	TCCR1B &= ~((1 << CS12) | (1 << CS10));
}

int main(void)
{
    i2c_init();   // Initialisation I2C
    init_segments();  // Configuration des segments en sortie
    init_digits(); // Configuration des digits en sortie
    adc_init(); // Initialisation de l'ADC
	sei();

	uint16_t number = 0;
    while (1)
	{
		timerOk = 0;
		init_timer();
		while (!timerOk)
		{
			number = adc_read(0); // Lire la valeur de l'ADC sur le canal 0
			display_number(number); // Afficher la valeur lue
		}
	}
}
