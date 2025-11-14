# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

# Directories
SRC_DIR = source
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Target executable
TARGET = $(BUILD_DIR)/memory_allocator

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/memalloc.c

# Object files
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/memalloc.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/memalloc.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

# Compile memalloc.c
$(OBJ_DIR)/memalloc.o: $(SRC_DIR)/memalloc.c $(SRC_DIR)/memalloc.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/memalloc.c -o $(OBJ_DIR)/memalloc.o

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/obj $(TARGET)
	@echo "Clean complete"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug with gdb
debug: $(TARGET)
	gdb $(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean run debug rebuild
