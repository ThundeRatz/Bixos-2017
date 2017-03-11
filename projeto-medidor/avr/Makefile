MCU=atmega8
F_CPU=8000000UL
TARGET?=avr-
CC=$(TARGET)gcc
SIZE=$(TARGET)size -C --mcu=$(MCU)
OBJCOPY=$(TARGET)objcopy -O ihex -R .eeprom

LFUSE = 0xE4
HFUSE = 0xD9

DBG=-g -gdwarf-2 -O0 -DSIMAVR_DEBUG
OPTIMIZE=-Os -flto
CFLAGS=-Wall -Wextra -mmcu=$(MCU) -DF_CPU=$(F_CPU)
ifdef SIMAVR_DEBUG
CFLAGS+=$(DBG) `pkg-config --cflags simavr-avr`
else
CFLAGS+=$(OPTIMIZE)
endif

PREFIX=build/
OUTPUT=$(PREFIX)transmissao_UART

AVRDUDE=avrdude -c usbasp -p $(MCU)

TARGETS:=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(TARGETS))
ALL_OBJECTS:=$(wildcard *.o)
# $< = prerequisito, $@ = alvo:
LINK=$(CC) $(OBJECTS) $(CFLAGS) -o $@ $(LDFLAGS)
RM=-rm -rf
MKDIR=mkdir -p
MAKEFILE_PATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
SOURCE_DIR:=$(dir $(MAKEFILE_PATH))

.PHONY: all clean install install_eeprom size

all: $(OUTPUT).axf

$(OUTPUT).axf: $(OBJECTS)
	$(MKDIR) $(PREFIX)
	$(LINK)
	$(OBJCOPY) $@ $(OUTPUT).hex

fuse:
	$(AVRDUDE) -B 10 -U lfuse:w:$(LFUSE):m
	$(AVRDUDE) -B 10 -U hfuse:w:$(HFUSE):m

install:
	$(AVRDUDE) -U flash:w:$(OUTPUT).hex:i

install_eeprom:
	$(AVRDUDE) -U eeprom:w:$(OUTPUT)_eeprom.bin

read:
	$(MKDIR) $(PREFIX)
	$(AVRDUDE) -U flash:r:$(OUTPUT)_read.bin:i
	$(AVRDUDE) -U lfuse:r:$(OUTPUT)_lfuse.bin:b
	$(AVRDUDE) -U hfuse:r:$(OUTPUT)_hfuse.bin:b
	$(AVRDUDE) -U eeprom:r:$(OUTPUT)_eeprom.bin:i

size:
	$(SIZE) $(OUTPUT).axf

clean:
	$(RM) $(ALL_OBJECTS) $(PREFIX)
