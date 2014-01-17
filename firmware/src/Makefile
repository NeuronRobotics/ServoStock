-include ../../../../toolchain/pic32/toolchain.mk
-include ../../device.mk


CFILES := $(wildcard *.c)
OFILES := $(CFILES:%.c=%.o)

all: $(OFILES)
	echo ok
%.o: %.c
	$(CC) -c  $<
clean:
	 rm -rf *.o