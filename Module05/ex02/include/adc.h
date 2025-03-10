#ifndef ADC_HPP
# define ADC_HPP

# include <avr/io.h>

void	adc_init(void);
uint16_t adc_read(uint8_t channel);
void	uint8_to_hex(uint8_t value, char* hex_string);
void	uint16_to_str(uint16_t value, char* dec_str);

#endif /* __ADC_HPP__ */
