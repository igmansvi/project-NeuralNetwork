# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = neuralNetwork

# Source files
SRCS = neuralNetwork.cpp neural.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)        $(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
%.o: %.cpp        $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
    rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
