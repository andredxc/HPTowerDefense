
all: main.cpp Game.o

	g++ -o HPTowerDefense main.cpp Game.o -lSDL2

debug: debugGame.o debugMain.o

	g++ -o HPTowerDefense main.cpp Game.o -g -lSDL2

Game.o:
	g++ -c Game.cpp -Wall -lSDL2

debugGame.o:
	g++ -c Game.cpp -Wall -g -lSDL2

clean:
	rm *.o HPTowerDefense
