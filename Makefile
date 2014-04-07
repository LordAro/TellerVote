CXX := clang++
CXXFLAGS += -c -Wall -Wextra -pedantic -g -std=c++11

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

all: tellervote

run: tellervote
	./tellervote

tellervote: $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJ) tellervote
