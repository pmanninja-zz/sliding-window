CXX=gcc
CXXFLAGS= -Wall
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
	 $(CLIENT)  \

$(SERVER): $(SRC_DIR)
	$(CXX) $(CXXFLAGS) $(GXXFLAGS) $(SERVER) \
	$(SRC_DIR)/server/*.c

sender: $(SERVER)
	$(SERVER)
	
$(CLIENT): $(SRC_DIR)
	$(CXX) $(CXXFLAGS) $(GXXFLAGS) $(CLIENT) \
	$(SRC_DIR)/client/*.c

reciever: $(CLIENT)
	$(CLIENT)