# Compiler
CXX = g++
#WCXX = x86_64-w64-mingw32-g++

# Directories
SRC_DIR = library
INC_DIR = include
OBJ_DIR = out
BIN_DIR = bin
TEST_DIR = test
DEMO_DIR = demo

# Compiler flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g -I$(INC_DIR)

# SFML library flags
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Add paths to the SFML headers and libraries for MinGW
#SFML_INCLUDE = /usr/local/sfml-windows/include
#SFML_LIB = /usr/local/sfml-windows/lib

# Source and object files
LIB_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(LIB_SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))
DEMO_SRCS = $(wildcard $(DEMO_DIR)/*.cpp)
DEMO_BIN = $(BIN_DIR)/menu
TERMINAL_BIN = $(BIN_DIR)/terminal

# Default target
all: $(TEST_BINS) $(DEMO_BIN) $(TERMINAL_BIN)

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

# Compile and link demo source file
$(DEMO_BIN): $(DEMO_DIR)/main.cpp $(LIB_OBJS) | $(BIN_DIR)
	@echo "Compiling demo $<..."
	$(CXX) $(CXXFLAGS) $< $(LIB_OBJS) -o $@ $(SFMLFLAGS)

# Compile and link terminal demo source file
$(TERMINAL_BIN): $(DEMO_DIR)/terminal.cpp $(LIB_OBJS) | $(BIN_DIR)
	@echo "Compiling terminal demo $<..."
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

# Run demo
demo: $(DEMO_BIN)
	@echo "Running demo..."
	./$(DEMO_BIN)

# Compile and run terminal demo
terminal: $(TERMINAL_BIN)
	@echo "Running terminal demo..."
	./$(TERMINAL_BIN)

# Add a cross-compile target for Windows
#cross-compile: $(DEMO_BIN)
#	$(WCXX) $(CXXFLAGS) -I$(INC_DIR) -I$(SFML_INCLUDE) demo/main.cpp $(LIB_OBJS) -o bin/menu.exe -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean test Linetest OpCodetest Operandtest Sectiontest Segmenttest Translatortest UItest demo terminal #cross-compile
