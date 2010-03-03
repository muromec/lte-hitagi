
all: backjump.bin

# arm-elf-gcc -D__KERNEL__ -I/home/muromec/source/linux-lte/include -Wall
# -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common
#  -fno-common -pi
#  pe -fno-builtin -D__linux__ -DNO_MM -mbig-endian  -march=armv4
#  -mtune=arm7tdmi -msoft-float   -nostdinc -iwithprefix include
#  -DKBUILD_BASENAME=io  -DEXPORT_SYM
#  TAB -o io.o -c io.c  

#backjump.o: backjump.S
#	arm-elf-as -k -EB  -o $@ $<

CFLAGS=-pie -mbig-endian -march=armv4 -mtune=arm7tdmi -O0

backjump.o: backjump.c
	arm-elf-gcc $(CFLAGS) -o backjump.o -c backjump.c 

backjump.elf: backjump.o
	arm-elf-ld --script link.lds $< -o $@

backjump.bin: backjump.elf
	arm-elf-objcopy -O binary $< $@

clean:
	rm -f backjump.bin backjump.o backjump.elf
