#include "i2c.h"
#include <util/delay.h>

// Fonction pour écrire dans un registre du PCA9555
void pca9555_write(uint8_t reg, uint8_t data) {
    i2c_start();
    i2c_write(I2C_ADDR << 1);  // Adresse en écriture
    i2c_write(reg);  // Sélection du registre
    i2c_write(data); // Envoi de la valeur
    i2c_stop();
}

// Fonction pour initialiser la LED D9 en sortie (P0_3)
void init_led(void) {
    // Mettre P0_3 en sortie (0 = sortie)
    pca9555_write(PCA9555_CONFIG_PORT0, (~(1 << D9_PIN) & 0xFF)); // 0b11110111
}

// Fonction pour faire clignoter la LED
void toggle_led(void) {
    static uint8_t led_state = 0;

    // Écrire dans le registre de sortie P0 (bit 3)
    if (led_state) {
        pca9555_write(PCA9555_OUTPUT_PORT0, (1 << D9_PIN));  // 0b00001000 Éteindre LED (actif bas)
    } else {
        pca9555_write(PCA9555_OUTPUT_PORT0, 0x00);  // Allumer LED
    }

    led_state = !led_state;
}

int main(void) {
    i2c_init();   // Initialisation I2C
    init_led();   // Configuration de la LED en sortie

    while (1) {
        toggle_led();  // Change l'état de la LED
        _delay_ms(500);  // Pause de 500ms (1 Hz)
    }
}

