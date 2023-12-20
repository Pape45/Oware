CC = gcc
CFLAGS = -I include
LDFLAGS = -L lib
LDLIBS = -lSDL2-2.0.0

SRC = main.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ) $(EXEC)
