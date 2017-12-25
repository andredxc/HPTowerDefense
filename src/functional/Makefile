GAME_NAME=hp
CC=g++

all: main.cpp Unit.o

	$(CC) -o $(GAME_NAME) main.cpp Unit.o -lSDL2 -lSDL2_image -lSDL2_ttf

debug: main.cpp debugUnit

	$(CC) -o $(GAME_NAME) main.cpp Unit.o -lSDL2 -lSDL2_image -lSDL2_ttf -g

Unit.o:
	$(CC) -c Unit.cpp -Wall -lSDL2

debugUnit:
	$(CC) -c Unit.cpp -Wall -lSDL2 -g

clean:
	rm *.o $(GAME_NAME)
