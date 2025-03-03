#include <avr/io.h>

void	ftdelay_ms(unsigned int ms)
{
	for (unsigned int i = 0; i < ms; i++)
		for (unsigned int j = 0; j < 1600; j++) // need 1600 clock cycle to make 1ms with a freq of 16MHz
			asm volatile ("nop"); // asm to insert an assembly instruction "nop" mean "No Operation" do nothing but take 1 clock cycle
}

int	main()
{
	DDRB |= (1 << PB1); // set PB1 to out (1)

	while (1)
	{
		PORTB ^= (1 << PB1); // change LED state
		ftdelay_ms(500); // wait 500 ms
	}
	return 0;
}
