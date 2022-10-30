CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -g -lSDL2 -lSDL2_ttf -lm -pg
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
EXEC = prog

all: $(EXEC)

$(EXEC) : main.o liste.o histo.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LFLAGS)

clean: 
	rm -rf *.o
