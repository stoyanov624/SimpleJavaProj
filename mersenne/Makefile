CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
SRCS     = src/main.cpp src/Mersenne.cpp src/Utils.cpp
OBJS     = $(SRCS:.cpp=.o)
TARGET   = mersenne

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp include/Mersenne.h include/Utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
