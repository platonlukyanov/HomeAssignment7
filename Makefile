IDIR=.
CXX=g++
CXXFLAGS=-I$(IDIR) -Wall -Wpedantic -Werror
LDFLAGS=-lgtest -lgtest_main -lpthread
OBJECT_FILES=CircularList.o
PROJECT=main
DEPS=CircularList.h
TEST_DIR=tests
TEST_FILES=$(wildcard $(TEST_DIR)/test-*.cpp)
TEST_OBJECTS=$(TEST_FILES:.cpp=.o) $(OBJECT_FILES)
ll: $(PROJECT);
default: all;

clean:
	rm -f $(PROJECT) $(TEST_DIR)/*.o *.o
format:
	find . \( -name '*.cpp' -o -name '*.h' \) -exec clang-format -i {} \;
$(PROJECT):
	@echo 'This project contains only test code. To run test suits, use "make test"';


test: $(TEST_OBJECTS)
	$(CXX) -o run_tests $^ $(LDFLAGS)
	./run_tests
	rm ./run_tests

$(TEST_DIR)/test-%.o: $(TEST_DIR)/test-%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
.PHONY: clean format $(PROJECT)
