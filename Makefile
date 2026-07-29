BUILD_DIR = build

.PHONY: all build clean

# Default target when running 'make'
all: build

# Target executed when running 'make build'
build:
	@cmake -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)

# Clean build directory
clean:
	@rm -rf $(BUILD_DIR)