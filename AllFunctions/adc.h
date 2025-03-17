#ifndef ADC_H
# define ADC_H

# include <avr/io.h>

void	adc_init8(void);
void	adc_init16(void);
uint8_t adc_read8(uint8_t channel);
uint16_t adc_read16(uint8_t channel);

#endif /* ADC_H */
