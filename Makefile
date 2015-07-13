LIB_SOURCE  = ./src/libs/
ALSA_SOURCE  = ./src/alsa/
MAIN_SOURCE = ./src/main/
CC = gcc

CFLAGS  = -c -I../inc/
LDFLAGS = -lm -lasound -pthread -lX11
PROGRAM = csynth

all: _bin
	cd build; \
	mv $(PROGRAM) ../ 
_bin: _libs
	cd $(MAIN_SOURCE); \
	$(CC) $(CFLAGS) synth.c; \
	mv *.o ../../build ; \
	cd ../../build ; \
	$(CC) -o $(PROGRAM) *.o $(LDFLAGS);
_libs:
	mkdir build ; \
	cd $(LIB_SOURCE); \
	$(CC) $(CFLAGS) *.c; \
	mv *.o ../../build ;
	cd $(ALSA_SOURCE); \
	$(CC) $(CFLAGS) *.c ; \
	mv *.o ../../build ;
install:
	rm -rf build; \
	mv $(PROGRAM) /usr/sbin;
clean:
	rm -rf build; \
	rm $(PROGRAM); \
