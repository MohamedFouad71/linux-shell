# Compiler 
CC = gcc

# Compiler Flags (for .c -> .o)
CFLAGS = -Wall -Wextra -Iinclude

# Linker Flags (for .o -> executable)
LDLIBS = -lreadline

# Source files
SRC = $(wildcard src/*.c) $(wildcard src/builtins/*.c) $(wildcard src/redirection/*.c) $(wildcard src/pipeline/*.c)

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = shell

# Default target
all: $(TARGET)

# Build the main program
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)