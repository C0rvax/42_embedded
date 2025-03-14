#ifndef I2C_H
# define I2C_H

# include <avr/io.h>


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
#define I2C_ADDR 0x20      // Adresse I2C of PCA9555
#define D9_PIN 3 // (100_3)
#define D10_PIN 2 // (100_2)
#define D11_PIN 1 // (100_1)
#define SW3_PIN 0 // (100_0)
#define TOFA_PIN 0 // datasheet board
#define TOFB_PIN 1 // datasheet board
#define TOFC_PIN 2 // datasheet board
#define TOFD_PIN 3 // datasheet board
#define TOFE_PIN 4 // datasheet board
#define TOFF_PIN 5 // datasheet board
#define TOFG_PIN 6 // datasheet board
#define TOFDTX_PIN 7 // datasheet board
#define TOFDP1_PIN 4 // datasheet board
#define TOFDP2_PIN 5 // datasheet board
#define TOFDP3_PIN 6 // datasheet board
#define TOFDP4_PIN 7 // datasheet board
#define PCA9555_CONFIG_PORT0  0x06 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_CONFIG_PORT1  0x07 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_OUTPUT_PORT0  0x02 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_OUTPUT_PORT1  0x03 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_INPUT_PORT0  0x00 // see section 6.2.1 of PCA9555 datasheet (p.6)

void	i2c_init(void);
void	i2c_start(void);
void	i2c_write( uint8_t data);
void	i2c_stop(void);
uint8_t	i2c_read(uint8_t ack);
void	i2c_write_status(const char* prompt);
void	pca9555_write(uint8_t reg, uint8_t data);
uint8_t pca9555_read(uint8_t reg);

#endif /* __I2C_H__ */
