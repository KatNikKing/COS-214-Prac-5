CXX := g++
CXXFLAGS = -std=c++11 -g -Wall -Werror

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := campusguard

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./campusguard

gdb: $(TARGET)
	gdb ./campusguard

valgrind: $(TARGET)
	valgrind --leak-check=full --keep-stacktraces=alloc-and-free --track-origins=yes ./campusguard
