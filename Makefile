CXX=clang++

C_FLAGS=-c -Wall -Wextra -pedantic -std=c++11  -O3  -DUNIT_TEST
L_FLAGS=

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
	
	