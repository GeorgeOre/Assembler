# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

# Source files
SRCS = Operand.cpp # IndexOperand.cpp bar.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = myprogram

# Default target
all: $(EXEC) run

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Run the executable
run:
	./$(EXEC)

# Clean
clean:
	rm -f $(OBJS) $(EXEC)
