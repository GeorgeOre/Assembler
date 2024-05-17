CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -Iinclude/OpCode/Parent -Iinclude/OpCode/Children -Iinclude/Operand/Parent -Iinclude/Operand/Children

# Directories
SRC_DIR = library
INCLUDE_DIR = include
OUT_DIR = out
TEST_DIR = test
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OUT_DIR)/%.o, $(TEST_FILES))

# Test executables
TEST_EXECUTABLES = $(patsubst $(OUT_DIR)/%.o, $(BIN_DIR)/%, $(TEST_OBJ_FILES))

# Rules
all: $(TEST_EXECUTABLES)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/SegmentTest: $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BIN_DIR)/SectionTest: $(OUT_DIR)/Section.o $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BIN_DIR)/OpCodeTest: $(OUT_DIR)/OpCode/Parent/OpCode.o $(OUT_DIR)/OpCode/Children/ALU_OpCode.o $(OUT_DIR)/OpCode/Children/B_OpCode.o $(OUT_DIR)/OpCode/Children/CTRL_OpCode.o $(OUT_DIR)/OpCode/Children/Misc_OpCode.o $(OUT_DIR)/OpCode/Children/W_OpCode.o $(OUT_DIR)/Section.o $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BIN_DIR)/OperandTest: $(OUT_DIR)/Operand/Parent/Operand.o $(OUT_DIR)/Operand/Children/Boperand.o $(OUT_DIR)/Operand/Children/Doperand.o $(OUT_DIR)/Operand/Children/Foperand.o $(OUT_DIR)/Operand/Children/Koperand.o $(OUT_DIR)/OpCode/Parent/OpCode.o $(OUT_DIR)/OpCode/Children/ALU_OpCode.o $(OUT_DIR)/OpCode/Children/B_OpCode.o $(OUT_DIR)/OpCode/Children/CTRL_OpCode.o $(OUT_DIR)/OpCode/Children/Misc_OpCode.o $(OUT_DIR)/OpCode/Children/W_OpCode.o $(OUT_DIR)/Section.o $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BIN_DIR)/LineTest: $(OUT_DIR)/Line.o $(OUT_DIR)/Operand/Parent/Operand.o $(OUT_DIR)/Operand/Children/Boperand.o $(OUT_DIR)/Operand/Children/Doperand.o $(OUT_DIR)/Operand/Children/Foperand.o $(OUT_DIR)/Operand/Children/Koperand.o $(OUT_DIR)/OpCode/Parent/OpCode.o $(OUT_DIR)/OpCode/Children/ALU_OpCode.o $(OUT_DIR)/OpCode/Children/B_OpCode.o $(OUT_DIR)/OpCode/Children/CTRL_OpCode.o $(OUT_DIR)/OpCode/Children/Misc_OpCode.o $(OUT_DIR)/OpCode/Children/W_OpCode.o $(OUT_DIR)/Section.o $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BIN_DIR)/TranslatorTest: $(OUT_DIR)/Translator.o $(OUT_DIR)/Line.o $(OUT_DIR)/Operand/Parent/Operand.o $(OUT_DIR)/Operand/Children/Boperand.o $(OUT_DIR)/Operand/Children/Doperand.o $(OUT_DIR)/Operand/Children/Foperand.o $(OUT_DIR)/Operand/Children/Koperand.o $(OUT_DIR)/OpCode/Parent/OpCode.o $(OUT_DIR)/OpCode/Children/ALU_OpCode.o $(OUT_DIR)/OpCode/Children/B_OpCode.o $(OUT_DIR)/OpCode/Children/CTRL_OpCode.o $(OUT_DIR)/OpCode/Children/Misc_OpCode.o $(OUT_DIR)/OpCode/Children/W_OpCode.o $(OUT_DIR)/Section.o $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BIN_DIR)/UITest: $(OUT_DIR)/UI.o $(OUT_DIR)/Translator.o $(OUT_DIR)/Line.o $(OUT_DIR)/Operand/Parent/Operand.o $(OUT_DIR)/Operand/Children/Boperand.o $(OUT_DIR)/Operand/Children/Doperand.o $(OUT_DIR)/Operand/Children/Foperand.o $(OUT_DIR)/Operand/Children/Koperand.o $(OUT_DIR)/OpCode/Parent/OpCode.o $(OUT_DIR)/OpCode/Children/ALU_OpCode.o $(OUT_DIR)/OpCode/Children/B_OpCode.o $(OUT_DIR)/OpCode/Children/CTRL_OpCode.o $(OUT_DIR)/OpCode/Children/Misc_OpCode.o $(OUT_DIR)/OpCode/Children/W_OpCode.o $(OUT_DIR)/Section.o $(OUT_DIR)/Segment.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@

.PHONY: clean run-tests

clean:
	rm -rf $(OUT_DIR) $(BIN_DIR)

run-tests: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		echo "Running $$test..."; \
		$$test; \
	done

# Individual test rules
run-segmenttest: $(BIN_DIR)/SegmentTest
	$(BIN_DIR)/SegmentTest

run-sectiontest: $(BIN_DIR)/SectionTest
	$(BIN_DIR)/SectionTest

run-opcodetest: $(BIN_DIR)/OpCodeTest
	$(BIN_DIR)/OpCodeTest

run-operandtest: $(BIN_DIR)/OperandTest
	$(BIN_DIR)/OperandTest

run-linetest: $(BIN_DIR)/LineTest
	$(BIN_DIR)/LineTest

run-translatortest: $(BIN_DIR)/TranslatorTest
	$(BIN_DIR)/TranslatorTest

run-uitest: $(BIN_DIR)/UITest
	$(BIN_DIR)/UITest
