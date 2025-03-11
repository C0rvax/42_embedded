#ifndef ADC_HPP
# define ADC_HPP

# include <avr/io.h>
#include <stdint.h>

void	adc_init(void);
uint16_t adc_read(void);
void	uint16_to_str(uint16_t value, char* dec_str);

#endif /* __ADC_HPP__ */
