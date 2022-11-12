CFLAGS = -c -Wall -ansi -pedantic -lm
CC = gcc
C_FILES = $(wildcard *.c)
O_FILES  = $(C_FILES:.c=.o)

.PHONY: all clean
.DEFAULT : all
all : main

main : $(O_FILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^

clean:
	-rm -f $(O_FILES)
	-rm -f main
