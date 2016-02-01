DEVICE = attiny13
CLOCK  = 1000000
PROGRAMMER = -P /dev/ttyUSB0 -c arduino
BAUDRATE   = -b 19200

help:
	@echo 'check => check connection with ATtiny13'
	@echo 'hex   => compile hex file'
	@echo 'flash => install hex file'
	@echo 'clean => delete unnecessary files'

check:
	avrdude -p $(DEVICE) $(PROGRAMMER) $(BAUDRATE)

hex:
	avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -c main.c
	avr-gcc -mmcu=$(DEVICE) -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex

flash:
	avrdude -p $(DEVICE) $(PROGRAMMER) -U flash:w:main.hex $(BAUDRATE)

clean:
	rm main.o
	rm main.elf
