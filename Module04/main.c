#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t duty_cycle = 0;
volatile int8_t step = 1; // Incrémente ou décrémente le rapport cyclique

void timer0_init() {
    // Mode CTC pour générer une interruption toutes les 4ms
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64
    OCR0A = 249;
    TIMSK0 = (1 << OCIE0A); // Activer l'interruption
}

void timer1_init() {
    // Fast PWM 8-bit
    TCCR1A = (1 << WGM10) | (1 << COM1A1);
    TCCR1B = (1 << WGM12) | (1 << CS11); // Prescaler 8
    DDRB |= (1 << PB1); // Configurer PB1 en sortie
}

void timer2_init() {
    // Mode CTC pour mise à jour progressive du duty cycle
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << CS22); // Prescaler 64
    OCR2A = 249;
    TIMSK2 = (1 << OCIE2A); // Activer l'interruption
}

ISR(TIMER0_COMPA_vect) {
    // Synchronisation : mise à jour de Timer1 et Timer2
    TCNT2 = 0; // Reset Timer2 pour garantir une mise à jour fluide
}

ISR(TIMER2_COMPA_vect) {
    duty_cycle += step;
    if (duty_cycle >= 255 || duty_cycle <= 0) {
        step = -step;
    }
    OCR1A = duty_cycle; // Mise à jour du PWM sur Timer1
}

int main() {
    cli(); // Désactiver les interruptions globales
    timer0_init();
    timer1_init();
    timer2_init();
    sei(); // Activer les interruptions globales

    while (1) {
        // La boucle principale reste vide, tout est géré par les ISR
    }
}

