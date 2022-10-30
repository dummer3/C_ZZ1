CC = gcc
CFLAGS = -Wall -Wextra
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
EXEC = $(SOURCES:.c=)

all: $(EXEC)

$(EXEC) : %: %.c 
	$(CC) $(CFLAGS) $< -o $@ -lm

clean: 
	rm -rf *.o
