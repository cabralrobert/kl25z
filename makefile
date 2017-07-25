all: clean bin/main.elf

CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

DEBUG_OPTS = -g3 -gdwarf-2 -gstrict-dwarf
OPTS = -Os
TARGET = -mcpu=cortex-m0
CFLAGS = -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" \
		 -fmessage-length=0 $(TARGET) -mthumb -mfloat-abi=soft \
		 $(DEBUG_OPTS) $(OPTS) -Iinc/

LIBOBJS = obj/_startup.o obj/syscalls.o obj/uart.o obj/delay.o obj/accel.o obj/touch.o obj/usb.o \
		obj/ring.o obj/tests.o obj/adc.o obj/gpio.o

obj/libbare.a: $(LIBOBJS)
	$(AR) -rv obj/libbare.a $(LIBOBJS)
	rm $(LIBOBJS) obj/*.lst

clean:
	rm -f obj/*.o obj/*.lst bin/*.out obj/libbare.a bin/*.dump bin/*.elf

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

bin/main.elf: bin/main.out
	$(OBJCOPY) -O srec bin/main.out bin/main.elf
	rm bin/*.out

obj/main.o: src/main.c
	$(CC) $(CFLAGS) $< -c -o $@

bin/main.out: obj/main.o inc/mkl25z4.ld obj/libbare.a
	$(CC) $(CFLAGS) -T inc/mkl25z4.ld -o $@ $< obj/libbare.a
