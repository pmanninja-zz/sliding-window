CXX=gcc
CXXFLAGS= -std=c++0x -g -fprofile-arcs -ftest-coverage -o
GXXFLAGS= -o -Wall

LINKFLAGS= -lgtest

SRC_DIR = src

TEST_DIR = test

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

PROGRAM_TEST= testProtocol

SERVER = server

CLIENT = client

.PHONY: all
all:  $(SERVER) $(CLIENT)

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o *.txt $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	*~ $(SRC_DIR)/*/.o  $(SRC_DIR)/*/server $(SRC_DIR)/*/client \
	 $(SERVER)  \
	 $(CLIENT)  \

$(SERVER): $(SRC_DIR)
	$(CXX) $(GXXFLAGS) $(SERVER) \
	$(SRC_DIR)/server/*.c
	
sender: $(SERVER)
	$(SERVER)
	
$(CLIENT): $(SRC_DIR)
	$(CXX) $(GXXFLAGS) $(CLIENT) \
	$(SRC_DIR)/client/*.c

reciever: $(CLIENT)
	$(CLIENT)

tests: $(TEST_DIR)
	$(CXX) $(CXXFLAGS) testProtocol $(INCLUDE) \
	$(TEST_DIR)/*  $(LINKFLAGS)

# tests: $(PROGRAM_TEST)
# 	$(PROGRAM_TEST)