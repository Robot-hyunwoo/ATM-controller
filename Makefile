# compiler option
CXX = g++
CXXFLAGS = -Wall -std=c++17

# default = demo
all: atm_demo
# atm_demo build
atm_demo: src/main.cpp src/atm_controller.cpp
	$(CXX) $(CXXLAGS) -o atm_demo.o src/main.cpp src/atm_controller.cpp

# test
test: atm_test
# atm_test build
atm_test: src/test_atm.cpp src/atm_controller.cpp
	$(CXX) $(CXXLAGS) -o atm_test.o src/test_atm.cpp src/atm_controller.cpp

# clean
clean:
	rm -f atm_demo atm_test