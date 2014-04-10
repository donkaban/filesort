CXX=g++

C_FLAGS=-c -Wall -Wextra -pedantic -std=c++11 -I/usr/local/include -O3 
L_FLAGS=-L/usr/local/lib 

TARGET=./test
SOURCES=main.cpp 
HEADERS=utils.h

OBJECTS=$(SOURCES:.cpp=.o)
.SUFFIXES: .cpp .o

all: $(SOURCES) $(HEADERS) $(TARGET) Makefile

$(TARGET): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(L_FLAGS) -o $@
	
.cpp.o: $(SOURCES) 
	$(CXX) $(C_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
	rm -f *.bin
	rm -f temp.*
	rm -f *.sorted
	
	