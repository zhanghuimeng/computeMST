SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:%.cpp=%.o)

TARGET=computeMST.exe
LIB=computeMST.a

all: $(TARGET) $(LIB)
$(TARGET): $(OBJECTS) $(HEADERS) $(LIB)
	@echo "Now Generating $(TARGET) ..."
	g++ $(OBJECTS) $(LIB) -o $(TARGET)
$(LIB): $(OBJECTS) $(HEADERS)
	@echo "Now Generating $(LIB) ..."
	ar -rv $(LIB) $(OBJECTS)
	ranlib $(LIB)
%.o: %.cpp $(HEADERS)
	@echo "Now Compiling $< ..."
	g++ -c $< -o $@ -std=c++11
clean:
	del *.o *.exe *.bak *.a
explain:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Lib: $(LIB)"
	@echo "Target: $(TARGET)"
