#ifndef ADC_HPP
# define ADC_HPP

# include <avr/io.h>

void	adc_init(void);
uint8_t adc_read(uint8_t channel);

#endif /* __ADC_HPP__ */
