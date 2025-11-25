CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = src/main.c src/stack.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = rpn_calculator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)

.PHONY: all clean
