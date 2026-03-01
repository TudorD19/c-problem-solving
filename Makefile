CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC_DIR=src
BIN_DIR=bin

SOURCES=$(wildcard $(SRC_DIR)/*.c)
TARGETS=$(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SOURCES))

all: $(TARGETS)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

list:
	@echo "Sources:"
	@ls -1 $(SRC_DIR)/*.c 2>/dev/null || true
	@echo ""
	@echo "Binaries:"
	@ls -1 $(BIN_DIR) 2>/dev/null || true
