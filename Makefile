# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=target/obj/%.o)
EXEC = target/$(shell basename `pwd`)

# Rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

target/obj/%.o: src/%.c target/obj/
	$(CC) $(CFLAGS) -c $< -o $@

target/obj/:
	mkdir -p $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all

run: all
	./$(EXEC)

.PHONY: all clean fclean re
