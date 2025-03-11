#ifndef LED_HPP
# define LED_HPP

# include <avr/io.h>

void	init_rgb(void);
void	set_rgb(uint8_t r, uint8_t g, uint8_t b);
void	wheel(uint8_t pos);
void	init_led(void);
void	set_led(uint8_t pos);

#endif /* __LED_HPP__ */
