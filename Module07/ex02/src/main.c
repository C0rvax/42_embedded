#include <avr/io.h>
#include <avr/eeprom.h>
//#include <string.h>
#include "prog.h"

#define EEPROM_SIZE 1024  // Taille EEPROM de l’AVR (ex: ATmega328P)
#define MAGIC_NUMBER 0x7F // Indicateur de données valides
#define MAX_KEY_SIZE 32
#define MAX_VALUE_SIZE 32

typedef struct {
    uint8_t magic;
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
} EEPROM_Pair;

// Fonction strcmp
int strcmp(const char *str1, const char *str2) {
    // Tant que les caractères de str1 et str2 sont égaux et qu'on n'a pas atteint la fin de l'une des chaînes
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            // Si les caractères sont différents, renvoyer la différence entre les deux
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        str1++;
        str2++;
    }

    // Si on a atteint la fin d'une chaîne, comparer les caractères nul ('\0')
    return (unsigned char)*str1 - (unsigned char)*str2;
}

// Fonction strncpy
char* strncpy(char *dest, const char *src, size_t n) {
    size_t i;

    // Copie des caractères de src vers dest, jusqu'à n caractères ou fin de la chaîne
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    // Si n est plus grand que la longueur de src, on remplit dest de '\0' jusqu'à n
    for (; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}

// Fonction pour trouver une clé dans l’EEPROM
int eeprom_find_key(const char *key, uint16_t *addr) {
    uint16_t i = 0;
    EEPROM_Pair pair;
    
    while (i < EEPROM_SIZE - sizeof(EEPROM_Pair)) {
        eeprom_read_block(&pair, (void *)i, sizeof(EEPROM_Pair));
        if (pair.magic == MAGIC_NUMBER && strcmp(pair.key, key) == 0) {
            *addr = i;
            return 1; // Clé trouvée
        }
        i += sizeof(EEPROM_Pair);
    }
    return 0; // Clé non trouvée
}

// Fonction pour trouver un emplacement libre
int eeprom_find_empty(uint16_t *addr) {
    uint16_t i = 0;
    EEPROM_Pair pair;

    while (i < EEPROM_SIZE - sizeof(EEPROM_Pair)) {
        eeprom_read_block(&pair, (void *)i, sizeof(EEPROM_Pair));
        if (pair.magic != MAGIC_NUMBER) {
            *addr = i;
            return 1;
        }
        i += sizeof(EEPROM_Pair);
    }
    return 0; // Pas d’espace libre
}

// Fonction pour écrire une paire clé/valeur
void eeprom_write_pair(const char *key, const char *value) {
    uint16_t addr;
    EEPROM_Pair pair;

    // Vérifier si la clé existe déjà
    if (eeprom_find_key(key, &addr)) {
        uart_tx_string("already exists\n");
        return;
    }

    // Trouver un espace libre
    if (!eeprom_find_empty(&addr)) {
        uart_tx_string("no space left\n");
        return;
    }

    // Écrire la paire
    pair.magic = MAGIC_NUMBER;
    strncpy(pair.key, key, MAX_KEY_SIZE);
    strncpy(pair.value, value, MAX_VALUE_SIZE);
    eeprom_write_block(&pair, (void *)addr, sizeof(EEPROM_Pair));

    // Afficher l’adresse où la paire est stockée
    uart_tx_string("Stored at: 0x");
    uart_print_status(addr >> 8);
    uart_print_status(addr & 0xFF);
    uart_tx('\n');
}

// Fonction pour lire une valeur à partir d’une clé
void eeprom_read_pair(const char *key) {
    uint16_t addr;
    EEPROM_Pair pair;

    if (eeprom_find_key(key, &addr)) {
        eeprom_read_block(&pair, (void *)addr, sizeof(EEPROM_Pair));
        uart_tx_string("\"");
        uart_tx_string(pair.value);
        uart_tx_string("\"\n");
    } else {
        uart_tx_string("empty\n");
    }
}

// Fonction pour supprimer une clé
void eeprom_forget_pair(const char *key) {
    uint16_t addr;
    if (eeprom_find_key(key, &addr)) {
        eeprom_write_byte((uint8_t *)addr, 0x00); // Efface le marqueur magique
        uart_tx_string("deleted\n");
    } else {
        uart_tx_string("not found\n");
    }
}

// Fonction pour afficher l'EEPROM
void eeprom_print() {
    for (uint16_t i = 0; i < EEPROM_SIZE; i++) {
        if (i % 16 == 0) {
            uart_tx_string("\n0x");
            uart_print_status(i >> 8);
            uart_print_status(i & 0xFF);
            uart_tx(':');
            uart_tx(' ');
        }
        uint8_t val = eeprom_read_byte((uint8_t *)i);
        uart_print_status(val);
        uart_tx(' ');
    }
    uart_tx('\n');
}


// Fonction principale
int main() {
    uart_init();
    uart_tx_string("EEPROM CLI Ready!\n");

    char command[10];
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];

    while (1) {
        uart_tx_string("> ");
        uart_rx_string(command, sizeof(command));

        if (strcmp(command, "READ") == 0) {
            uart_rx_string(key, MAX_KEY_SIZE);
            eeprom_read_pair(key);
        } 
        else if (strcmp(command, "WRITE") == 0) {
            uart_rx_string(key, MAX_KEY_SIZE);
            uart_rx_string(value, MAX_VALUE_SIZE);
            eeprom_write_pair(key, value);
        } 
        else if (strcmp(command, "FORGET") == 0) {
            uart_rx_string(key, MAX_KEY_SIZE);
            eeprom_forget_pair(key);
        } 
        else if (strcmp(command, "PRINT") == 0) {
            eeprom_print();
        } 
        else {
            uart_tx_string("Invalid command\n");
        }
    }
}

