#ifndef I2C_H
# define I2C_H

# include <avr/io.h>
/*
* TWI Two Wire Interface
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

#define F_CPU 16000000UL  // MCU frequency
#define F_SCL 100000UL    // I2C frequency (100 kHz)
#define TWBR_VALUE ((F_CPU / F_SCL - 16) / 2)  // (p.180)
#define I2C_ADDR 0x20      // I2C address of PCA9555
#define D9_PIN 3 // (100_3)
#define D10_PIN 2 // (100_2)
#define D11_PIN 1 // (100_1)
#define SW3_PIN 0 // (100_0)
#define PCA9555_CONFIG_PORT0  0x06 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_CONFIG_PORT1  0x07 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_OUTPUT_PORT0  0x02 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_OUTPUT_PORT1  0x03 // see section 6.2.1 of PCA9555 datasheet (p.6)
#define PCA9555_INPUT_PORT0  0x00 // see section 6.2.1 of PCA9555 datasheet (p.6)

/**
 * @brief Initialize the I2C interface.
 */
void i2c_init(void);

/**
 * @brief Start the I2C communication.
 */
void i2c_start(void);

/**
 * @brief Write data to the I2C bus.
 * 
 * @param data The data to write.
 */
void i2c_write(uint8_t data);

/**
 * @brief Stop the I2C communication.
 */
void i2c_stop(void);

/**
 * @brief Read data from the I2C bus.
 * 
 * @param ack Acknowledge bit.
 * @return The read data.
 */
uint8_t i2c_read(uint8_t ack);

/**
 * @brief Write a status message to the I2C bus.
 * 
 * @param prompt The status message.
 */
void i2c_write_status(const char* prompt);

/**
 * @brief Write data to a PCA9555 register.
 * 
 * @param reg The register to write to.
 * @param data The data to write.
 */
void pca9555_write(uint8_t reg, uint8_t data);

/**
 * @brief Read data from a PCA9555 register.
 * 
 * @param reg The register to read from.
 * @return The read data.
 */
uint8_t pca9555_read(uint8_t reg);

#endif /* __I2C_H__ */
