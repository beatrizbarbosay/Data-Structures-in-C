CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cobra

cobra: cobra.o funcoes.o
	gcc cobra.o funcoes.o $(LDFLAGS) -o cobra 

cobra.o: cobra.c funcoes.o funcoes.h
	gcc $(CFLAGS) -c cobra.c

funcoes.o: funcoes.c funcoes.h
	gcc $(CFLAGS) -c funcoes.c

clean:
	rm -f cobra
