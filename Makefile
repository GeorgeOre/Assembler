<<<<<<< Updated upstream
# {[(	Compiler and Linker Settings	)]}

# C Compiler
CC := gcc
# C++ Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -Wall -Wextra -O3 -g #-std=c++11
# Linker flags
LDFLAGS := -lm  # Example of additional linker flags if needed

# {[(	Main Project Config	)]}

# Output directory for object files
BUILD_DIR := bin
SRC_DIRS := library obj-parent obj-children

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
#SRCS := $(wildcard $(SRC_DIRS)/*)
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP
OBJ_DIR := out
# Source files
#SRCS := $(wildcard *.cpp)
# Create object file paths
#OBJS := $(OBJ_DIR)/$(subst .cpp,.o,$(notdir $(SRCS)))
# Create the name of the assembler executable
EXEC := assembler

# {[(	Test Configs	)]}

# Test files directory
TEST_DIR := test
# Build test source files
TEST_SRC := $(wildcard $(TEST_DIR)/*.cpp)
# Build test object files
TEST_OBJ := $(OBJ_DIR)/$(subst .cpp,.o,$(notdir $(TEST_SRC)))
# Name the test executable
TEST_BIN := runtest

# Test_Operand files directory
TEST_OPERAND_DIR := Operand/Parent Operand/Children
# Build test source files
TEST_OPERAND_SRC := $(wildcard $(TEST_OPERAND_DIR)/*.cpp) $(wildcard $(TEST_OPERAND_DIR)/*/*.hh)
# Build test object files
TEST_OPERAND_OBJ := $(OBJ_DIR)/$(subst .cpp,.o,$(notdir $(TEST_SRC)))
# Name the test executable
TEST_OPERAND_BIN := operand_test

# {[(	Target Configs	)]}

# Default target for the assembler
all: $(EXEC)
	./$(EXEC)
# Link the object files into the assembler
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o bins/$(EXEC) $(LDFLAGS)
# Compile source files into object files
$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS) -o $(OBJS)

# Run the test executable
t: $(TEST_BIN)
	./$(TEST_BIN)
# Link the test object files into test executable
$(TEST_BIN): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o bin/$(TEST_BIN) $(LDFLAGS)
# Compile the test source files
$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

# Run the test_operand executable
test_operand: $(TEST_BIN)
	./$(TEST_BIN)
# Link the test object files into test executable
$(TEST_BIN): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o bin/$(TEST_BIN) $(LDFLAGS)
# Compile the test source files
$(TEST_OBJ): $(TEST_SRC)
	echo $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

check:
	@echo "Source directories:"
	@echo $(SRC_DIRS)
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
#	echo -e Sources:\n$(SRCS)
#	echo -e Test Sources:\n$(TEST_SRC)

.PHONY: clean test all check

# Clean
clean:
	rm -f $(EXEC) $(OBJS) $(TEST_BIN) $(TEST_OBJ)









=======
# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR) -I$(INC_DIR)/Operand/Parent -I$(INC_DIR)/Operand/Children -I$(INC_DIR)/OpCode/Parent -I$(INC_DIR)/OpCode/Children

# Directories
SRC_DIR = library
OBJ_DIR = out
BIN_DIR = bin
INC_DIR = include
TEST_DIR = tests
DEMO_DIR = demo

# Files
MAIN_SRC = $(DEMO_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/OperandTest.cpp
EXECUTABLE = $(BIN_DIR)/myprogram
TEST_EXECUTABLE = $(BIN_DIR)/runtest

# Source files
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Operand specific source and object files
OPERAND_SRC_FILES = $(shell find $(SRC_DIR)/Operand -name '*.cpp')
OPERAND_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(OPERAND_SRC_FILES))

# Create the necessary directories
$(OBJ_FILES): | $(OBJ_DIR)
$(EXECUTABLE): | $(BIN_DIR)
$(TEST_EXECUTABLE): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/OpCode/Children
	mkdir -p $(OBJ_DIR)/OpCode/Parent
	mkdir -p $(OBJ_DIR)/Operand/Children
	mkdir -p $(OBJ_DIR)/Operand/Parent

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target for the main executable
$(EXECUTABLE): $(OBJ_FILES) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Operand tests executable
operand_test: $(OPERAND_OBJ_FILES) $(TEST_DIR)/OperandTest.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/operand_test $^ $(LDFLAGS)

# Phony targets
.PHONY: all clean run operand_test operand_test_run

# Default target
all: $(EXECUTABLE)

# Run the main program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Run the operand tests
operand_test_run: operand_test
	./$(BIN_DIR)/operand_test

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(EXECUTABLE) $(TEST_EXECUTABLE)
>>>>>>> Stashed changes
