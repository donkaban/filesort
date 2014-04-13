CXX=clang++

C_FLAGS=-c -Wall -Wextra -pedantic -std=c++11  -O3 

TARGET=./test
SOURCES=main.cpp 
HEADERS=common.h chunk.h splittedFile.h

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(HEADERS) $(TARGET) Makefile
	rm -f $(OBJECTS)

$(TARGET): $(OBJECTS) $(HEADERS)  Makefile
	$(CXX) $(OBJECTS) -o $@
	
.cpp.o: $(SOURCES)  $(HEADERS) 
	$(CXX) $(C_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
	rm -f *.bin*
	
	