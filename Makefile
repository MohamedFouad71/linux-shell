# Compiler 
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Iinclude

# Source files
SRC = $(wildcard src/*.c) $(wildcard src/builtins/*.c) $(wildcard src/redirection/*.c)

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = shell

# Default target
all: $(TARGET)

# Build the main program
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
