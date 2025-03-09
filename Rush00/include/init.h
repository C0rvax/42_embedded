#ifndef INIT_HPP
# define INIT_HPP

# include <avr/io.h>
# include <avr/interrupt.h>
# include <util/twi.h>

void	init_led(void);
void	init_but(void);
ISR(INT0_vect);
ISR(PCINT2_vect);

#endif /* __INIT_HPP__ */
