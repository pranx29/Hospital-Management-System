# Compiler
CC=gcc
# Compiler flags
CFLAGS=-Wall
# Directories
IDIR=include
SDIR=src
BDIR=bin

# Source files
SRCS=$(wildcard $(SDIR)/*.c)

# Target executable
TARGET=main

# Default target
all: $(TARGET)

# Linking all source files into executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -I$(IDIR) $^ -o $(TARGET)

# Clean target to remove executable
clean:
	rm -rf $(TARGET)

.PHONY: all clean
