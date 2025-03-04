#include <avr/io.h>
#include <util/delay.h>

int	main()
{
	DDRB |= (1 << PB1); // set PB1 to out (1)
	DDRD &= ~((1 << PD2) | (1 << PD4)); // set PD2 and PD4 to in (1)
	PORTD |= (1 << PD2) | (1 << PD3); // set pull-up res for PD2 and PD4

	// configure Timer1 in mode Fast PWM (Mode 14) with ICR1 for TOP
	TCCR1A |= (1 << COM1A1); // Mode PWM, OC1A "Clear on compare Match" (page 109)
	TCCR1A |= (1 << WGM11); // Mode Fast PWM with ICR1 TOP and OCR1A at BOTTOM (mode 14, page 109)
	TCCR1B |= (1 << WGM12) | (1 << WGM13); // Mode Fast PWM with ICR1 and OCR1A at BOTTOM (mode 14, page 109)
	TCCR1B |= (1 << CS12) | (1 << CS10); // with a prescaler of 1024 (page 110)
	
	ICR1 = 15625; // set TOP = 1s (15625 * 1024 = 16 Hz)

	uint16_t tCycle = 1562; // 10% of ICR1
	OCR1A = tCycle;

	uint8_t prevSw1State = 1;
	uint8_t prevSw2State = 1;

	while (1)
	{
		uint8_t sw1State = PIND & (1 << PD2);
		uint8_t sw2State = PIND & (1 << PD4);

		if (!sw1State && prevSw1State)
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD2)))
			{
				if (tCycle <= 14062) // max 90%
					tCycle += 1562;
			}
		}
		if (!sw2State && prevSw2State)
		{
			if (!(PIND & (1 << PD4)))
			{
				_delay_ms(50);
				if (tCycle >= 1562) // min 10%
					tCycle -= 1562;
			}
		}
		OCR1A = tCycle;
		prevSw1State = sw1State;
		prevSw2State = sw2State;
	}

	return 0;
}
