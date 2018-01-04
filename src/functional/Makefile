GAME_NAME=hp
CC=g++ -std=c++11

all: main.cpp Unit.o AttackUnit.o DefenceUnit.o Game.o Projectile.o

	$(CC) -o $(GAME_NAME) main.cpp Unit.o AttackUnit.o DefenceUnit.o Game.o Projectile.o -lSDL2 -lSDL2_image -lSDL2_ttf

debug: main.cpp debugUnit debugAttackUnit debugDefenceUnit debugGame debugProjectile

	$(CC) -o $(GAME_NAME) main.cpp Unit.o AttackUnit.o DefenceUnit.o Game.o Projectile.o -lSDL2 -lSDL2_image -lSDL2_ttf -g

Unit.o:
	$(CC) -c Unit.cpp -Wall -lSDL2

debugUnit:
	$(CC) -c Unit.cpp -Wall -lSDL2 -g

AttackUnit.o:
	$(CC) -c AttackUnit.cpp -Wall -lSDL2

debugAttackUnit:
	$(CC) -c AttackUnit.cpp -Wall -lSDL2 -g

DefenceUnit.o:
	$(CC) -c DefenceUnit.cpp -Wall -lSDL2

debugDefenceUnit:
	$(CC) -c DefenceUnit.cpp -Wall -lSDL2 -g

Game.o:
	$(CC) -c Game.cpp -Wall -lSDL2

debugGame:
	$(CC) -c Game.cpp -Wall -lSDL2 -g

Projectile.o:
	$(CC) -c Projectile.cpp -Wall -lSDL2

debugProjectile:
	$(CC) -c Projectile.cpp -Wall -lSDL2 -g

clean:
	rm *.o $(GAME_NAME)
