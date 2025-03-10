#include <avr/io.h>
#include <util/delay.h>

// Fonction d'initialisation de l'ADC
void adc_init(void) {
    // Sélection de la tension de référence AVCC et du canal ADC0 (potentiomètre)
    ADMUX = (1 << REFS0) | (1 << ADLAR); // AVCC comme référence, 8-bit (ADLAR = gauche)
    
    // Activation de l'ADC, prédivision par 128 pour une bonne précision (~125kHz à 16MHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Fonction de lecture de l'ADC (8 bits)
uint8_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Sélectionner le canal d'entrée (0-15)
    ADCSRA |= (1 << ADSC); // Démarrer la conversion
    while (ADCSRA & (1 << ADSC)); // Attendre la fin de la conversion
    return ADCH; // Retourner la valeur 8-bit
}

// Fonction pour transmettre un caractère via UART
void uart_transmit(char c) {
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit vide
    UDR0 = c; // Envoyer le caractère
}

// Fonction pour transmettre une valeur en hexadécimal
void print_hex(uint8_t value) {
    // Convertir la valeur en hexadécimal (2 chiffres hex)
    char high = (value >> 4) & 0x0F; // Récupérer les 4 bits de poids fort
    char low = value & 0x0F; // Récupérer les 4 bits de poids faible

    // Convertir les valeurs en caractères hex (0-9, A-F)
    if (high < 10) {
        uart_transmit(high + '0'); // Si entre 0 et 9, afficher le chiffre
    } else {
        uart_transmit(high - 10 + 'A'); // Si entre A et F, afficher la lettre
    }

    if (low < 10) {
        uart_transmit(low + '0'); // Idem pour le bas
    } else {
        uart_transmit(low - 10 + 'A');
    }

    uart_transmit('\n'); // Nouvelle ligne après la valeur
}

int main(void) {
    adc_init(); // Initialisation de l'ADC

    // Configuration UART (9600 bauds, 8N1)
    UBRR0H = 0;
    UBRR0L = 103; // Pour 9600 bauds avec un quartz 16MHz
    UCSR0B = (1 << TXEN0); // Activer la transmission
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Format 8 bits

    while (1) {
        // Lire les trois capteurs : Potentiomètre (ADC0), LDR (ADC1), NTC (ADC2)
        uint8_t potentiometer = adc_read(0); // Canal 0 : RV1
        uint8_t ldr = adc_read(1); // Canal 1 : LDR (R14)
        uint8_t ntc = adc_read(2); // Canal 2 : NTC (R20)

        // Afficher les valeurs en hexadécimal
        print_hex(potentiometer); // Afficher la valeur du potentiomètre
        print_hex(ldr); // Afficher la valeur de la LDR
        print_hex(ntc); // Afficher la valeur de la NTC

        _delay_ms(20); // Attendre 20 ms
    }

    return 0;
}

