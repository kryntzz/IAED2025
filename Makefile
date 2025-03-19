CC = gcc
CFLAGS = -Iinclude -O3 -Wall -Wextra -Werror -Wno-unused-result
SRC = main.c $(wildcard include/*.c)
EXEC = proj

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC)

.PHONY: all clean
