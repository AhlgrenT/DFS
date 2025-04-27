# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinc

BIN_DIR := ./bin
BUILD_DIR := ./build
SRC_DIR := ./src

################# Setup #################
#dirs
MASTER := $(BIN_DIR)/master
SLAVE := $(BIN_DIR)/slave
CLIENT := $(BIN_DIR)/client

# Find all .cpp files
SRC_MASTER := $(shell find $(SRC_DIR)/master -name '*.cpp')
SRC_SLAVE := $(shell find $(SRC_DIR)/slave -name '*.cpp')
SRC_CLIENT := $(shell find $(SRC_DIR)/client -name '*.cpp')
SRC_COMMON := $(shell find $(SRC_DIR)/common -name '*.cpp')

# Object files
OBJ_MASTER := $(patsubst $(SRC_DIR)/master/%.cpp, $(BUILD_DIR)/master/%.o, $(SRC_MASTER))
OBJ_SLAVE := $(patsubst $(SRC_DIR)/slave/%.cpp, $(BUILD_DIR)/slave/%.o, $(SRC_SLAVE))
OBJ_CLIENT := $(patsubst $(SRC_DIR)/client/%.cpp, $(BUILD_DIR)/client/%.o, $(SRC_CLIENT))
OBJ_COMMON := $(patsubst $(SRC_DIR)/common/%.cpp, $(BUILD_DIR)/common/%.o, $(SRC_COMMON))

################## Targets ######################
.PHONY: all
all: master slave client

.PHONY: master
master: $(MASTER)

.PHONE: slave
slave:  $(SLAVE)

.PHONY: client
client: $(CLIENT)

################## Linking #####################
$(MASTER): $(OBJ_MASTER) $(OBJ_COMMON)
	@echo "Linking $(MASTER)..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SLAVE): $(OBJ_SLAVE) $(OBJ_COMMON)
	@echo "Linking $(SLAVE)..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CLIENT): $(OBJ_CLIENT) $(OBJ_COMMON)
	@echo "Linking $(CLIENT)..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

################# Compiling #####################

$(BUILD_DIR)/master/%.o: $(SRC_DIR)/master/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/slave/%.o: $(SRC_DIR)/slave/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/client/%.o: $(SRC_DIR)/client/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(BUILD_DIR)/common/%.o: $(SRC_DIR)/common/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -rf $(BIN_DIR)/*
	rm -rf $(BUILD_DIR)/*

