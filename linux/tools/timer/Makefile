# needed environment variables
# (shold be set by the reconos toolchain)
# CROSS_COMPILE

# export CROSS_COMPILE=gcc-arm-linux-gnueabihf

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

OBJS := timer.o

CFLAGS = -O2 -g -Wall

all: libtimer.a

libtimer.a: $(OBJS)
	$(AR) -rcsv libtimer.a $(OBJS)

clean:
	rm -f *.o *.a
