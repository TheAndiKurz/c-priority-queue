# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = $(shell find src -name *.c)
OBJ = $(SRC:src/%.c=target/obj/%.o)
EXEC = target/$(shell basename `pwd`)

# Rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

target/obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -fr target

re: fclean all

run: all
	./$(EXEC)

.PHONY: all clean fclean re
