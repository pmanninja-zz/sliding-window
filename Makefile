# CXX = g++
# CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
# LDFLAGS =  -fsanitize=address

# SRC = 
# OBJ = $(SRC:.cc=.o)
# EXEC = server client

# all: $(EXEC)

# $(EXEC): $(OBJ)
# 	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

# clean:
# 	rm -rf $(OBJ) $(EXEC)

CXX=gcc
CXXFLAGS= clang
GXXFLAGS= -o

LINKFLAGS= -lgtest

SRC_DIR = src


SERVER = server

CLIENT = client

.PHONY: all
all:  $(SERVER) $(CLIENT)

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC_DIR)/*/.o  $(SRC_DIR)/*/server $(SRC_DIR)/*/client \
	 $(SERVER)  \

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