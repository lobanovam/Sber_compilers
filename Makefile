CC = g++
IFLAGS = -I./include/
FLAGS =

SRC = ./src/flexScanner.cpp ./src/driver.cpp ./src/tokenizer.cpp

OBJ_TEMP = $(subst ./src/, ./src/build/, $(SRC))
OBJ      = $(subst .cpp,.o, $(OBJ_TEMP))

all: $(OBJ)
	$(CC) $(FLAGS) $(IFLAGS) $^ -o main        # $^ - всё что справа от all:

./src/build/%.o: ./src/%.cpp
	mkdir -p ./src/build
	$(CC) $(FLAGS) $(IFLAGS) -c  $^ -o $@	   # $@ - всё что слева 

flex:
	flex -o ./src/flexScanner.cpp ./generator/flexScanner.l

run:
	./main < test.txt

clear: 
	rm -f ./src/build/*.o main 
