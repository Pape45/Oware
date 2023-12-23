CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -Llib
LDLIBS = -lSDL2-2.0.0

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = bin/game

all: $(EXEC)
	rm -f $(OBJ)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
