CC = gcc
CFLAGS = -std=c99

SRC = mcst3.c cmpfunc.c countlines.c sort.c swap.c sizeoffile.c

OUTPUT = t3

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC)
	
clean:
	rm -f $(OUTPUT)