#ifndef SPI_H
# define SPI_H

# include <avr/io.h>
# include <util/delay.h>

# define BRIGHTNESS 2

/**
 * @brief Initialize the SPI as Master.
 */
void	SPI_MasterInit(void);

/**
 * @brief Transmit data via SPI.
 * 
 * @param cData Data to be transmitted.
 */
void	SPI_MasterTransmit(uint8_t cData);

/**
 * @brief Send data to APA102 LED.
 * 
 * @param brightness Brightness level of the LED.
 * @param red Red color value.
 * @param green Green color value.
 * @param blue Blue color value.
 */
void	APA102_send(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Control APA102 LED.
 * 
 * @param led LED index.
 * @param brightness Brightness level of the LED.
 * @param red Red color value.
 * @param green Green color value.
 * @param blue Blue color value.
 */
void	APA102(uint8_t led, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);

#endif /* SPI_H */
