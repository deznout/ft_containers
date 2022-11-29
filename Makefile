CXX			= c++

CXXFLAGS 	= -g -Wall -Wextra -Werror -std=c++98

all: start_vector start_stack start_set start_map

VECTOR		= vector_test

$(VECTOR):
	@($(CXX) $(CXXFLAGS) ./tests/test_vector.cpp -o $(VECTOR))

start_vector: $(VECTOR)
			@./$(VECTOR)
			@rm $(VECTOR)
			@rm -rf ./vector_test.dSYM

STACK		= stack_test

$(STACK):
	@($(CXX) $(CXXFLAGS) ./tests/test_stack.cpp -o $(STACK))

start_stack: $(STACK)
			@./$(STACK)
			@rm $(STACK)
			@rm -rf ./stack_test.dSYM

SET		= set_test

CPP_SET = ./tests/test_set.cpp

$(SET):
	@($(CXX) $(CXXFLAGS) $(CPP_SET) -o $(SET))

start_set: $(SET)
			@./$(SET)
			@rm $(SET)
			@rm -rf ./set_test.dSYM

MAP		= map_test

CPP_MAP = ./tests/test_map.cpp

$(MAP):
	@($(CXX) $(CXXFLAGS) $(CPP_MAP) -o $(MAP))

start_map: $(MAP)
			@./$(MAP)
			@rm $(MAP)
			@rm -rf ./map_test.dSYM