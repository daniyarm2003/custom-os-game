BINARY_DIR ?= bin
BINARY_FILE ?= imageconvert

SOURCE_DIR ?= src
SOURCE_FILE ?= image_converter.cpp

CXX := g++
CFLAGS ?= -Wall -std=c++2a

.PHONY: clean

$(BINARY_DIR)/$(BINARY_FILE): $(SOURCE_DIR)/$(SOURCE_FILE) | $(BINARY_DIR)
	$(CXX) $(CFLAGS) -o $(BINARY_DIR)/$(BINARY_FILE) $(SOURCE_DIR)/$(SOURCE_FILE)

$(BINARY_DIR):
	mkdir $(BINARY_DIR)

clean:
	rm -rf $(BINARY_DIR)