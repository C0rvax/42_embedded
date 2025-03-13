#ifndef SPI_H
# define SPI_H

# define BRIGHTNESS 2

#include <avr/io.h>
#include <util/delay.h>

void	SPI_MasterInit(void);
void	SPI_MasterTransmit(uint8_t cData);
void	APA102_send(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void	APA102(uint8_t led, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);

#endif /* __SPI_H__ */
