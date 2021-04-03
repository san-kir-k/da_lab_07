CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
NAME = lab07

all:
	$(CXX) $(CXXFLAGS) main.cpp -o $(NAME)
clean:
	rm -f *.o $(NAME)