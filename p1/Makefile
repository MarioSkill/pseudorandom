# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c++11 -Wall

# the build target executable:
TARGET = Axiomas
TARGET2 = Distributions

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp ../bigint/Big*.cc Statistics.cpp Utils.cpp

dist: $(TARGET2)

$(TARGET2): $(TARGET2).cpp
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).cpp Utils.cpp Plot.cpp


clean:
	$(RM) $(TARGET) statistics utils
	$(RM) $(TARGET2)