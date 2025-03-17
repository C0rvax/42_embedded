#ifndef ADC_H
# define ADC_H

# include <avr/io.h>

/*
* ADMUX ADC Multiplexer Selection Register
* ADCSRA ADC Control and Status Register A
* ADSC ADC Start Conversion
*/

/**
 * @brief Initialize the ADC for 8-bit resolution.
 */
void adc_init8(void);

/**
 * @brief Initialize the ADC for 10-bit resolution.
 */
void adc_init16(void);

/**
 * @brief Read an 8-bit value from the ADC.
 * 
 * @param channel The ADC channel to read from.
 * @return The 8-bit ADC value.
 */
uint8_t adc_read8(uint8_t channel);

/**
 * @brief Read a 10-bit value from the ADC.
 * 
 * @param channel The ADC channel to read from.
 * @return The 10-bit ADC value.
 */
uint16_t adc_read16(uint8_t channel);

#endif /* ADC_H */
