C_SRC = $(wildcard *.c)
C_OBJ = $(patsubst %.c, %.o, $(C_SRC))
CC=gcc
CFLAGS=-c 
all: main

main: ${C_OBJ}
	$(CC) ${C_OBJ} -o $@

${C_OBJ}:%.o:%.c
	$(CC) $(CFLAGS) $<  -o $@


clean:
	rm -r main *.o
.PHONY: all clean

