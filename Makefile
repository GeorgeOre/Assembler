# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
INCLUDES = -Iinclude -Iinclude/OpCode/Parent -Iinclude/OpCode/Children -Iinclude/Operand/Parent -Iinclude/Operand/Children
LIB_DIR = library
OBJ_DIR = out
BIN_DIR = bin
TEST_DIR = test

# Source Files
SRC = $(wildcard $(LIB_DIR)/*.cpp) \
      $(wildcard $(LIB_DIR)/OpCode/Parent/*.cpp) \
      $(wildcard $(LIB_DIR)/OpCode/Children/*.cpp) \
      $(wildcard $(LIB_DIR)/Operand/Parent/*.cpp) \
      $(wildcard $(LIB_DIR)/Operand/Children/*.cpp)

# Object Files
OBJ = $(SRC:$(LIB_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Test Files
TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BIN = $(TEST_SRC:$(TEST_DIR)/%.cpp=$(BIN_DIR)/%)

# Targets
all: $(TEST_BIN)

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR)/%: $(OBJ) $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Define individual test targets
LineTest: $(BIN_DIR)/LineTest
	@$(BIN_DIR)/LineTest

OpCodeTest: $(BIN_DIR)/OpCodeTest
	@$(BIN_DIR)/OpCodeTest

OperandTest: $(BIN_DIR)/OperandTest
	@$(BIN_DIR)/OperandTest

SectionTest: $(BIN_DIR)/SectionTest
	@$(BIN_DIR)/SectionTest

SegmentTest: $(BIN_DIR)/SegmentTest
	@$(BIN_DIR)/SegmentTest

TranslatorTest: $(BIN_DIR)/TranslatorTest
	@$(BIN_DIR)/TranslatorTest

UITest: $(BIN_DIR)/UITest
	@$(BIN_DIR)/UITest

run-tests: $(TEST_BIN)
	@for test in $(TEST_BIN); do \
		$$test; \
	done

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run-tests LineTest OpCodeTest OperandTest SectionTest SegmentTest TranslatorTest UITest
