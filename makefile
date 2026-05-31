# DESATUALIZADO!!! use o cmake ou conserte esse makefile :)
# CXX := g++
# CXXFLAGS := -std=c++17 -Wall -Wextra -g -Isrc -MMD -MP 

# SRC_DIR := src
# BUILD_DIR := build

# SRC := $(shell find $(SRC_DIR) -name "*.cpp")
# OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
# DEP := $(OBJ:.o=.d)

# TARGET := MetodosNum2

# all: $(BUILD_DIR)/$(TARGET)

# $(BUILD_DIR)/$(TARGET): $(OBJ)
# 	@mkdir -p $(BUILD_DIR)
# 	$(CXX) $(INCLUDES) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

# -include $(DEP)

# clean:
# 	rm -f $(OBJ) $(DEP) $(BUILD_DIR)/$(TARGET)

# run: all
# 	$(BUILD_DIR)/$(TARGET)

all:
	@echo DESATUALIZADO!!! use o cmake ou conserte esse makefile :)