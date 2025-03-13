#ifndef I2C_HPP
# define I2C_HPP

# include <avr/io.h>
#include <stdint.h>


/*
* TWI Two Wire service Interface
* TWBR TW Baud Rate
* TWSR TW Status Register
* TWCR TW Control Register
* TWEN TW ENable
* TWSTA TW STArt
* TWSTO TW STOp
* TWINT TW INTerrupt flag
* TWDR TW Data Register
* TWAR TW Address Register
* Write (low) 0
* Read (high) 1
*/

#define F_CPU 16000000UL  // Freq mcu
#define F_SCL 100000UL    // Freq I2C (100 kHz)
#define TWBR_VALUE ((F_CPU / F_SCL - 16) / 2)  // (p.180)
#define AH20_ADDRESS 0x38

void	i2c_init(void);
void	i2c_start(void);
void	i2c_write( uint8_t data);
void	i2c_stop(void);
uint8_t	i2c_read(uint8_t ack);
void	i2c_write_status(const char* prompt);
void    pca9555_init(uint8_t address);

#endif /* __I2C_HPP__ */
