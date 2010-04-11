
CFLAGS=-pie -mbig-endian -march=armv4 -mtune=arm7tdmi -O0

SOURCES=start.c string.c memcpy.c parse.c handle.c usb.c dump.c nor.c
OBJECTS=$(SOURCES:.c=.o)

NAME=lte-hitagi
BINARY=$(NAME).bin
ELF=$(NAME).elf

all: $(BINARY)

.c.o:
	arm-elf-gcc $(CFLAGS) -o $@ -c $<

$(ELF): $(OBJECTS)
	arm-elf-ld --script link.lds $(OBJECTS) -o $@

$(BINARY): $(ELF)
	arm-elf-objcopy -O binary $< $@

clean:
	rm -f $(BINARY) $(ELF) $(OBJECTS)
