#OBJS specifies which files to compile as part of the project
OBJS = main.o predefined.o texture.o gameLoop.o character.o background.o

#Compiler of choice
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#include folder
H = src/headers/

#source folder
S = src/implementations/

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Ninja

$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: $HgameLoop.h $Hpredefined.h $Smain.cpp
	$(CC) $(COMPILER_FLAGS) -c $Smain.cpp

predefined.o: $Spredefined.cpp
	$(CC) $(COMPILER_FLAGS) -c $Spredefined.cpp

texture.o: $Stexture.cpp
	$(CC) $(COMPILER_FLAGS) -c $Stexture.cpp

gameLoop.o: $SgameLoop.cpp $Hpredefined.h $Hbackground.h
	$(CC) $(COMPILER_FLAGS) -c $SgameLoop.cpp

character.o: $Scharacter.cpp
	$(CC) $(COMPILER_FLAGS) -c $Scharacter.cpp
	
background.o: $Sbackground.cpp
	$(CC) $(COMPILER_FLAGS) -c $Sbackground.cpp
	
clean:
	rm *.o $(OBJ_NAME)