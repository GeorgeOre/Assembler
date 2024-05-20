# Compiler
CXX = g++

# Directories
SRC_DIR = library
INC_DIR = include
OBJ_DIR = out
BIN_DIR = bin
TEST_DIR = test

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR)

# Source and object files
LIB_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(LIB_SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

# Default target
all: $(TEST_BINS)

# Create directories if they do not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile library source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile and link each test source file separately
$(BIN_DIR)/%: $(TEST_DIR)/%.cpp $(LIB_OBJS) | $(BIN_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $< $(LIB_OBJS) -o $@

# Test all
test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Test Line
Linetest: $(BIN_DIR)/LineTest
	./$(BIN_DIR)/LineTest

# Test OpCode
OpCodetest: $(BIN_DIR)/OpCodeTest
	./$(BIN_DIR)/OpCodeTest

# Test Operand
Operandtest: $(BIN_DIR)/OperandTest
	./$(BIN_DIR)/OperandTest

# Test Section
Sectiontest: $(BIN_DIR)/SectionTest
	./$(BIN_DIR)/SectionTest

# Test Segment
Segmenttest: $(BIN_DIR)/SegmentTest
	./$(BIN_DIR)/SegmentTest

# Test Translator
Translatortest: $(BIN_DIR)/TranslatorTest
	./$(BIN_DIR)/TranslatorTest

# Test UI
UItest: $(BIN_DIR)/UITest
	./$(BIN_DIR)/UITest

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean test Linetest OpCodetest Operandtest Sectiontest Segmenttest Translatortest UItest
