CXX=g++

C_FLAGS=-c -Wall -Wextra -pedantic -std=c++11 -I/usr/local/include -O3  -DUNIT_TEST
L_FLAGS=-L/usr/local/lib 

TARGET=./test
SOURCES=main.cpp 
HEADERS=common.h chunk.h

OBJECTS=$(SOURCES:.cpp=.o)
.SUFFIXES: .cpp .o

all: $(SOURCES) $(HEADERS) $(TARGET) Makefile
	rm -f $(OBJECTS)

$(TARGET): $(OBJECTS) $(HEADERS)  Makefile
	$(CXX) $(OBJECTS) $(L_FLAGS) -o $@
	
.cpp.o: $(SOURCES)  $(HEADERS) 
	$(CXX) $(C_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
	rm -f *.bin
	rm -f temp.*
	rm -f *.sorted
	
	