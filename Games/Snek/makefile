#OBJS specifies which files to compile as part of the project
OBJS = main.o gameLoop.o preparations.o block.o head.o body.o eatables.o

#Compiler of choice
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = SnekTheGame

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: src/implementations/main.cpp src/headers/gameLoop.h
	${CC} $(COMPILER_FLAGS) -c src/implementations/main.cpp

gameLoop.o: src/implementations/gameLoop.cpp src/headers/gameLoop.h src/headers/preparations.h src/headers/block.h src/headers/eatables.h
	$(CC) $(COMPILER_FLAGS) -c src/implementations/gameLoop.cpp

preparations.o: src/implementations/preparations.cpp src/headers/preparations.h
	$(CC) $(COMPILER_FLAGS) -c src/implementations/preparations.cpp

block.o: src/implementations/block.cpp src/headers/block.h
	$(CC) $(COMPILER_FLAGS) -c src/implementations/block.cpp

head.o: src/implementations/head.cpp src/headers/head.h src/headers/block.h
	$(CC) $(COMPILER_FLAGS) -c src/implementations/head.cpp

body.o: src/implementations/body.cpp src/headers/body.h src/headers/block.h
	$(CC) $(COMPILER_FLAGS) -c src/implementations/body.cpp

eatables.o: src/implementations/eatables.cpp src/headers/eatables.h src/headers/block.h
	$(CC) $(COMPILER_FLAGS) -c src/implementations/eatables.cpp

clean:
	rm -f *.o
	