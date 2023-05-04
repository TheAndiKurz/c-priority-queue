# create a makefile for a c project with multiple files in src folder
# put the object files in a folder called obj in the target folder
# put the executable in the target folder

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

target/obj/%.o: src/%.c
	mkdir -p target/obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all

run: all
	./$(EXEC)

.PHONY: all clean fclean re
