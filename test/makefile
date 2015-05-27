CXX=g++ -std=c++11 -Wall -pedantic
LDFLAGS=-I/usr/include
LIBS=
PROJECT='Datanet'
TARGET=Datanet

SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)

common_objects = SocketException.o
simple_server_objects = $(common_objects) ServerSocket.o Socket.o simple_server_main.o
simple_client_objects = $(common_objects) ClientSocket.o Socket.o simple_client_main.o

all: simple_server simple_client

simple_server: $(simple_server_objects)
	$(CXX) $(LDFLAGS) $(LIBS) -o simple_server $(simple_server_objects)

simple_client: $(simple_client_objects)
	$(CXX) $(LDFLAGS) $(LIBS) -o simple_client $(simple_client_objects)

%.o: %.cpp
	@echo "Compiling $<.."
	@$(CXX) $(LDFLAGS) $(LIBS) -c $< -o $@

simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp

clean:
	rm -f *.o simple_server simple_client

class:
	./.cpp_class.sh $(NAME) $(PROJECT)
	echo "Created $(NAME) class"

.PHONY: clean class
