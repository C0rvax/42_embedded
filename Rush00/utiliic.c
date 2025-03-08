#include <avr/io.h>
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
#define SLAVE_ADDRESS 0x08  // ??? Rdm 

void	init_master(void)
{
    TWBR = (uint8_t)TWBR_VALUE;  // Bus Speed (p.198)
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  // (p.183) (1 << TWIE) enable interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for TWINT flag set (p.183)
	if (!(TWSR & 0x08)) // Check if Status different from start (p.183)
		ERROR();
}

void	stop_master(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void	init_slave(void)
{
    TWAR = address << 1; // (p.191)
    TWCR = (1 << TWEA) | (1 << TWEN);
}

void master_t(uint8_t data)
{
    TWDR = (SLAVE_ADDRESS << 1) | 0x0; // load SLAVE_ADDRESS + W (0) into data register
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission of address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set (SLA+W has been transmited)
	if (!(TWSR & 0x18))
		ERROR();
    TWDR = data; // load data into data register
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission of address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set (data has been transmited)
	if (!(TWSR & 0x28))
		ERROR();
}

uint8_t slave_r(uint8_t address)
{
    while (!(TWCR & (1 << TWINT)));
	if (!(TWSR & 0x60))
		ERROR();
    while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0x80))
		return TWDR;
	return 0;
}

int main()
{
	init_master();
	init_slave();
    while (1);
}
