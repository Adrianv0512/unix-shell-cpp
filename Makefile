CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
SRC := src/main.cpp
BIN := minishell

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)