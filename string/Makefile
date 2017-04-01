#child makefile

OFILES=mtscat.o module.o
CFILES=mtscat.c module.c
include ../Make.cfg

string_error:;@echo This makefile must be called by the main Makefile

string.unix.a:$(CFILES)
	$(CC) $(CFLAGS-UNIX) mtscat.c -o mtscat.o
	$(CC) $(CFLAGS-UNIX) module.c -o module.o
	ar rcs string.unix.a $(OFILES)


string.a:$(CFILES)
	$(CC) $(CFLAGS-WIN) mtscat.c -o mtscat.o
	$(CC) $(CFLAGS-WIN) module.c -o module.o
	ar rcs string.a $(OFILES)
