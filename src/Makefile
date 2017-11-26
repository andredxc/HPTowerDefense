GAME_NAME=HPTowerDefence
CC=g++

all: main.cpp Game.o Unit.o AttackUnit.o DefenceUnit.o Soldier.o Archer.o Horseman.o Projectile.o

	$(CC) -o $(GAME_NAME) main.cpp Game.o Unit.o AttackUnit.o DefenceUnit.o Soldier.o Archer.o Horseman.o Projectile.o -lSDL2 -lSDL2_image

debug: main.cpp debugGame debugUnit debugAttackUnit debugSoldier debugArher debugDefenceUnit debugHorseman debugProjectile

	$(CC) -o $(GAME_NAME) main.cpp Game.o Unit.o AttackUnit.o DefenceUnit.o Soldier.o Archer.o Horseman.o Projectile.o -lSDL2 -g -lSDL2_image

Game.o:
	$(CC) -c Game.cpp  -Wall -lSDL2

Unit.o:
	$(CC) -c Unit.cpp -Wall -lSDL2

AttackUnit.o:
	$(CC) -c AttackUnit.cpp -Wall -lSDL2

DefenceUnit.o:
	$(CC) -c DefenceUnit.cpp -Wall -lSDL2

Soldier.o:
	$(CC) -c Soldier.cpp -Wall -lSDL2

Horseman.o:
	$(CC) -c Horseman.cpp -Wall -lSDL2

Archer.o:
	$(CC) -c Archer.cpp -Wall -lSDL2 -lSDL2_image

TroopList.o:
	$(CC) -c TroopList.cpp -Wall

Projectile.o:
	$(CC) -c Projectile.cpp -Wall -lSDL2 -lSDL2_image

debugGame:
	$(CC) -c Game.cpp -Wall -lSDL2 -g

debugUnit:
	$(CC) -c Unit.cpp -Wall -lSDL2 -g

debugDefenceUnit:
	$(CC) -c DefenceUnit.cpp -Wall -lSDL2 -g

debugHorseman:
	$(CC) -c Horseman.cpp -Wall -lSDL2 -g

debugAttackUnit:
	$(CC) -c AttackUnit.cpp -Wall -lSDL2 -g

debugSoldier:
	$(CC) -c Soldier.cpp -Wall -lSDL2 -g

debugArcher:
	$(CC) -c Archer.cpp -Wall -lSDL2 -g

debugTroopList:
	$(CC) -c TroopList.cpp -Wall -g

debugProjectile:
	$(CC) -c Projectile.cpp -Wall -lSDL2 -lSDL2_image -g

clean:
	rm *.o $(GAME_NAME)
