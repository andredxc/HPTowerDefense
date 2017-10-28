GAME_NAME=HPTowerDefense
CC=g++

all: main.cpp Game.o Unit.o

	$(CC) -o $(GAME_NAME) main.cpp Game.o -lSDL2

debug: debugMain.o debugGame.o debugUnit.o

	$(CC) -o $(GAME_NAME) main.cpp Game.o -lSDL2 -g

Game.o:
	$(CC) -c Game.cpp -Wall -lSDL2

Unit.o:
	$(CC) -c Unit.cpp -Wall -lSDL2

debugGame.o:
	$(CC) -c Game.cpp -Wall -lSDL2 -g

debugUnit.o:
	$(CC) -c Unit.cpp -Wall -lSDL2 -g

clean:
	rm *.o $(GAME_NAME)
