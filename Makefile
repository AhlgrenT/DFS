# Compiler & flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files (recursively find all .cpp files)
SRC = $(shell find $(SRC_DIR) -name "*.cpp")

# Generate matching .o paths by replacing src/ with build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Final executable
TARGET = $(BIN_DIR)/DFS

# Default target
all: $(TARGET)

# Link all .o files into the binary
$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile each .cpp to a .o, mirroring folder structure
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	find $(BUILD_DIR) -type f \( -name '*.o' -o -name '*.d' \) -delete
	find $(BIN_DIR) -type f -delete


.PHONY: all clean
