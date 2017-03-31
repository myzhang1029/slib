#child makefile

OFILES=mtscat.o module.o
CFILES=mtscat.c module.c
CFLAGS-WIN=-c -O2 -DPLAT=1 -l../include
CFLAGS-UNIX=-c -O2 -DPLAT=0 -l../include

string-unix:string.a.unix

string.a.unix:$(CFILES)
	gcc $(CFLAGS-UNIX) mtscat.c -o mtscat.o
	gcc $(CFLAGS-UNIX) module.c -o module.o
	ar rcs string.a.unix $(OFILES)

string-win:string.a

string.a:$(CFILES)
	gcc $(CFLAGS-WIN) mtscat.c -o mtscat.o
	gcc $(CFLAGS-WIN) module.c -o module.o
	ar rcs string.a $(OFILES)
