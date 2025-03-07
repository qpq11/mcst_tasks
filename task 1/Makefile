CXX = g++
CXXFLAGS = -pthread

SRC = mcst1.cpp

OUTPUT = t1

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC)
	
clean:
	rm -f $(OUTPUT).exe