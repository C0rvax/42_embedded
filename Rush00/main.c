#include <avr/io.h>
#include <stdint.h>
#include <util/twi.h>
#include "prog.h"
#include "init.h"

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

volatile uint8_t master = 0;
volatile uint8_t started = 0;

void	init_master(void)
{
    TWBR = (uint8_t)TWBR_VALUE;  // Bus Speed (p.198)
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  // (p.183) (1 << TWIE) enable interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for TWINT flag set (p.183)
	if ((TWSR & 0xF8) != TW_START) // Check if Status different from start (p.183)
		ERROR();
	master = 1;
}

void	start_game(void)
{

	started = 1;
}

void	stop_game(void)
{
	started = 0;
}

void	count_down(void)
{
	PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
	_delay_ms(1000);
	PORTB &= ~(1 << PB0);
	_delay_ms(1000);
	PORTB &= ~(1 << PB1);
	_delay_ms(1000);
	PORTB &= ~(1 << PB2);
	_delay_ms(1000);
	PORTB &= ~(1 << PB4);
}

void	stop_master(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void	init_slave(void)
{
    TWAR = SLAVE_ADDRESS << 1; // (p.191)
    TWCR = (1 << TWEA) | (1 << TWEN);
}

void master_t(uint8_t data)
{
    TWDR = (SLAVE_ADDRESS << 1) | TW_WRITE; // load SLAVE_ADDRESS + W (0) into data register
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission of address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set (SLA+W has been transmited)
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
		ERROR();
    TWDR = data; // load data into data register
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission of address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set (data has been transmited)
	if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
		ERROR();
}

uint8_t master_r(void)
{
    TWDR = (SLAVE_ADDRESS << 1) | TW_READ; // load SLAVE_ADDRESS + R (1) into data register
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission of address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set (SLA+W has been transmited)
	if ((TWSR & 0xF8) != TW_MR_SLA_ACK)
		ERROR();
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission of address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set (SLA+W has been transmited)
	if ((TWSR & 0xF8) == TW_MR_DATA_ACK)
		return TWDR;
	return 0;
}

uint8_t slave_r(uint8_t address)
{
    while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_SR_SLA_ACK)
		ERROR();
    while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) == TW_SR_DATA_ACK)
		return TWDR;
	return 0;
}

int main()
{
	init_but();
	init_led();
	init_slave();
    while (1);
}
