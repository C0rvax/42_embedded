#include "i2c.h"

void	i2c_init(void)
{
	TWSR = 0; // prescaler 1
	TWBR = (uint8_t)TWBR_VALUE;
}

void	i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void	i2c_start(void)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void	i2c_stop(void)
{
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

uint8_t	i2c_read(uint8_t ack)
{
	if (ack)
		TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	else
		TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

// Fonction pour écrire dans un registre du PCA9555
void pca9555_write(uint8_t reg, uint8_t data)
{
    i2c_start();
    i2c_write(I2C_ADDR << 1);  // Adresse en écriture
    i2c_write(reg);  // Sélection du registre
    i2c_write(data); // Envoi de la valeur
    i2c_stop();
}

// Fonction pour lire un registre du PCA9555
uint8_t pca9555_read(uint8_t reg)
{
    uint8_t data;
    i2c_start();
    i2c_write(I2C_ADDR << 1);  // Adresse en écriture
    i2c_write(reg);  // Sélection du registre
    i2c_start();
    i2c_write((I2C_ADDR << 1) | 1);  // Adresse en lecture
    data = i2c_read(0); // Lire la valeur
    i2c_stop();
    return data;
}
