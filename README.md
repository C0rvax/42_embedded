# Embedded Systems Cursus - ATmega328P Programming

![42 School](https://img.shields.io/badge/École_42-Embedded_Systems_Pool-black?style=for-the-badge&logo=42)![C](https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge&logo=c)![AVR](https://img.shields.io/badge/Microcontroller-ATmega328P-orange.svg?style=for-the-badge)![Makefile](https://img.shields.io/badge/Build_System-Makefile-lightgrey.svg?style=for-the-badge&logo=gnu-make)

Welcome to my Embedded Systems Pool repository!

This repository centralizes all my solutions for the 42 Embedded Systems "Piscine" (intensive bootcamp). The program's objective is to build foundational skills in C-based embedded systems programming by directly manipulating the registers of an **AVR ATmega328P** microcontroller on a custom development board.

Each module represents a distinct technical challenge, starting from basic GPIO manipulation and progressing to complex communication protocols like I2C and SPI.

## 📚 Table of Contents

1.  [The Devkit: 42Chips Devboard](#-the-devkit-42chips-devboard)
2.  [Environment and Toolchain](#-environment-and-toolchain)
3.  [Repository Structure](#-repository-structure)
4.  [Modules Overview](#-modules-overview)
    - [Module 00: GPIO & First Programs](#module-00--gpio--first-programs)
    - [Module 01: Timers](#module-01--timers)
    - [Module 02: UART Protocol](#module-02--uart-protocol)
    - [Module 03: RGB & Advanced Timers (PWM)](#module-03--rgb--advanced-timers-pwm)
    - [Module 04: Interrupts](#module-04--interrupts)
    - [Module 05: Analog-to-Digital Converter (ADC)](#module-05--analog-to-digital-converter-adc)
    - [Module 06: I2C Protocol](#module-06--i2c-protocol)
    - [Module 07: EEPROM](#module-07--eeprom)
    - [Module 08: SPI Protocol](#module-08--spi-protocol)
    - [Module 09: I/O Expander & 7-Segment Display](#module-09--io-expander--7-segment-display)
    - [Rush 00: Multiplayer Game](#rush-00--multiplayer-game)
5.  [Author](#-author)

---

## 🔌 The Devkit: 42Chips Devboard

All exercises were completed on the custom **42Chips Devboard**, which is based on an **ATmega328P** microcontroller.

![Devboard Schematic](https://github.com/C0rvax/embeded/blob/main/elec42_pool.jpg?raw=true)

#### Key Components:
*   **Microcontroller**: Atmel ATmega328P (the same one found in the Arduino Uno).
*   **Programming/Debug**: USB-C via a CH340G USB-to-UART converter.
*   **GPIOs**: 4 LEDs, 1 RGB LED, 2 push-buttons.
*   **I2C Peripherals**: Real-Time Clock (RTC), Temperature/Humidity sensor, 16-bit I/O Expander (controlling a 7-segment display, 3 LEDs, 1 button).
*   **SPI Peripherals**: 3 addressable RGB LEDs (APA102).
*   **Analog Sensors (ADC)**: Potentiometer, Light Dependent Resistor (LDR), NTC thermistor.

---

## 🛠️ Environment and Toolchain

*   **Toolchain**: `avr-gcc` for cross-compiling C code for the AVR architecture.
*   **Build System**: `make` with custom `Makefile`s for each project.
*   **Programming**: `avrdude` to flash the compiled `.hex` files onto the microcontroller.
    *   **Programmer**: `arduino`
    *   **Baudrate**: `115200`

---

## 📁 Repository Structure

The repository is organized into modules, where each directory corresponds to a key concept in embedded systems programming.

```
.
├── module00_gpio/
├── module01_timers/
├── module02_uart/
├── module03_rgb_pwm/
├── module04_interrupts/
├── module05_adc/
├── module06_i2c/
├── module07_eeprom/
├── module08_spi/
├── module09_expander_7seg/
└── rush00_multiplayer/
```

---

## 📖 Modules Overview

### Module 00: GPIO & First Programs
*   **Description**: An introduction to basic General-Purpose Input/Output (GPIO) operations.
*   **Skills Acquired**: Configuring `DDRX` (Data Direction), `PORTX` (Output), and `PINX` (Input) registers. Managing pin states, reading button inputs, and performing fundamental bitwise operations.

### Module 01: Timers
*   **Description**: Using hardware timers to perform time-based tasks and generate Pulse-Width Modulation (PWM) signals without blocking the CPU.
*   **Skills Acquired**: Configuring timers in CTC (Clear Timer on Compare Match) mode, calculating prescalers, generating PWM signals, and controlling duty cycles.

### Module 02: UART Protocol
*   **Description**: Implementing serial communication to exchange data between the microcontroller and a computer.
*   **Skills Acquired**: Configuring the UART protocol, sending and receiving characters and strings, and using UART interrupts for non-blocking communication.

### Module 03: RGB & Advanced Timers (PWM)
*   **Description**: Controlling complex colors on an RGB LED using advanced PWM techniques.
*   **Skills Acquired**: Generating multiple PWM signals to drive the R, G, and B channels independently. Creating smooth color transitions and enabling interactive control via UART.

### Module 04: Interrupts
*   **Description**: Event-driven programming for improved responsiveness and CPU efficiency.
*   **Skills Acquired**: Handling external interrupts (triggered by buttons) and timer-based interrupts. Designing reactive programs without empty `while(1)` loops.

### Module 05: Analog-to-Digital Converter (ADC)
*   **Description**: Reading analog signals (variable voltages) using the built-in ADC.
*   **Skills Acquired**: Configuring the ADC, reading data from analog sensors (potentiometer, LDR), and managing resolution (8-bit vs. 10-bit).

### Module 06: I2C Protocol
*   **Description**: Communicating with complex peripheral devices over a 2-wire bus (SDA/SCL).
*   **Skills Acquired**: Implementing the I2C master protocol, interfacing with external sensors (AHT20), and reading datasheets to format data correctly.

### Module 07: EEPROM
*   **Description**: Using non-volatile memory to store persistent data that survives a power cycle.
*   **Skills Acquired**: Reading from and writing to the internal EEPROM. Implementing a persistent key-value storage system.

### Module 08: SPI Protocol
*   **Description**: Communicating with peripherals over a fast, synchronous serial bus.
*   **Skills Acquired**: Configuring the SPI bus in master mode. Controlling daisy-chained devices like addressable APA102 LEDs.

### Module 09: I/O Expander & 7-Segment Display
*   **Description**: Expanding the number of available GPIOs with an I2C I/O expander to drive a 7-segment display.
*   **Skills Acquired**: Controlling a PCA9555PW I/O expander. Implementing time-division multiplexing to display multiple digits on a single display.

### Rush 00: Multiplayer Game
![I2C](https://img.shields.io/badge/Tech-I2C_Multi--Master-blueviolet.svg?style=for-the-badge)*   **Description**: A group project to create a game by making two microcontrollers communicate with each other.
*   **Objective**: Build a two-player reflex game where two devkits communicate over the I2C bus.
*   **Key Skills**: I2C communication between two microcontrollers (one master, one slave), synchronization, and designing a simple game protocol.

---

## 👤 Author

*   **Arthur Duvillaret**
*   **42 Login**: `aduvilla`
*   **GitHub**: [@C0rvax](https://github.com/C0rvax)
*   **LinkedIn**: [Arthur Duvillaret](https://www.linkedin.com/in/arthur-duvillaret-427912377/)
