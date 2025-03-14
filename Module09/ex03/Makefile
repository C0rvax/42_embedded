# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 11:03:44 by aduvilla          #+#    #+#              #
#    Updated: 2025/03/14 20:14:44 by aduvilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= avr-gcc # compilator for AVR in C

OBJCOPY		= avr-objcopy # convert bin to hex

AVRDUDE		= avrdude # tool to load the pgm in flash memory

PROGRAMMER	= arduino # programmer used to load bootloader

MCU			= atmega328p # microcontroller model

F_CPU		= 16000000UL # microcontroller frequency (16MHz)

PORT		= /dev/ttyUSB0 # board port

BAUD		= 115200 # com speed between microcontroller and computer (115200 with arduino programmer)

FLAGS		= -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -pedantic -Iinclude -g # -Os -> optimize for size

SRCS		= $(addprefix src/, main.c i2c.c)

TARGET		= main

all			: hex flash

$(TARGET).bin:
	$(CC) $(FLAGS) -o $(TARGET).bin $(SRCS)

hex			: $(TARGET).bin
	$(OBJCOPY) -O ihex $(TARGET).bin $(TARGET).hex

flash		:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i # (-U <memtype>:<op>:<filename>:<format>) upload in memory flash with write operation the file main.hex in Intel HEX format

clean		:
	rm -f $(TARGET).bin $(TARGET).hex

re			: clean all

.PHONY		: all hex flash clean re
