#ifndef SPI_HPP
# define SPI_HPP

#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);

#endif /* __SPI_HPP__ */
