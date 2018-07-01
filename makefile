# Output decorators
GREEN = "\\033[32m"
RESET = "\\033[0m"

# Build options
CC = g++
CFLAGS = -std=c++11 -g
LDFLAGS =

# Phony targets
.PHONY: all clean


# Default target
all: game
	@echo "$(GREEN)Build successful!$(RESET)"


# Build targets
game: game.o
	@echo "$(GREEN)Linking executable main ...$(RESET)"
	$(CC) $(LDFLAGS) $^ -o $@

game.o: game.cpp goGameBase.h
	@echo "$(GREEN)Compiling main.o ...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm game game.o
