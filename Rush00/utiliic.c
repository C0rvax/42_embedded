#include <avr/io.h>
#define F_CPU 16000000UL  // Fréquence de l'ATmega328P (16 MHz)
#define F_SCL 100000UL    // Fréquence I2C (100 kHz)
#define TWBR_VALUE ((F_CPU / F_SCL - 16) / 2)  // Calcul du registre TWBR
#define SLAVE_ADDRESS 0x10  // Adresse du Slave

void I2C_Master_Init() {
    TWBR = (uint8_t)TWBR_VALUE;  // Définit la vitesse du bus
    TWSR = 0x00;  // Pas de prescaler
}

void I2C_Start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);  // Envoi du Start
    while (!(TWCR & (1 << TWINT)));  // Attente de la fin de transmission
}

void I2C_Slave_Init(uint8_t address) {
    TWAR = address << 1;
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
}

void I2C_Stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void I2C_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}
uint8_t I2C_Slave_Receive() {
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}


int main() {
    I2C_Master_Init();  // Init Master
    I2C_Slave_Init(SLAVE_ADDRESS);  // Init Slave

    while (1) {
        I2C_Start();
        I2C_Write(SLAVE_ADDRESS << 1);  // Envoi de l'adresse du Slave
        I2C_Write(0x42);  // Envoi d'une donnée (exemple)
        I2C_Stop();
    }
    return 0;
}
int main() {
    I2C_Slave_Init(SLAVE_ADDRESS);

    while (1) {
        uint8_t data = I2C_Slave_Receive();  // Attend une donnée
        if (data == 0x42) {
            // Action en réponse au Master
        }
    }
    return 0;
}
-----------------------------------
-----------------------------------------

// Déclaration des fonctions
uint8_t I2C_TryMaster();

// Détection du rôle
uint8_t isMaster = 0; // 1 = Master, 0 = Slave

int main() {
    // Vérification si on peut être Master
    if (I2C_TryMaster()) {
        isMaster = 1;
        I2C_Master_Init();
    } else {
        isMaster = 0;
        I2C_Slave_Init(SLAVE_ADDRESS);
    }

    while (1) {
        if (isMaster) {
            // Code du Master
            I2C_Start();
            I2C_Write(SLAVE_ADDRESS << 1);
            I2C_Write(0x42); // Envoi d'une donnée exemple
            I2C_Stop();
            _delay_ms(1000);
        } else {
            // Code du Slave
            uint8_t data = I2C_Slave_Receive();
            if (data == 0x42) {
                // Réaction au Master
            }
        }
    }
}
uint8_t I2C_TryMaster() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    _delay_ms(10); // Petit délai pour tester
    if (TWCR & (1 << TWINT)) {
        return 1; // On peut être Master
    } else {
        return 0; // On est Slave
    }
}
