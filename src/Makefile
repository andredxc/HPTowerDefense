GAME_NAME=HPTowerDefense
CC=g++

all: main.cpp Game.o Unit.o AttackUnit.o DefenceUnit.o Soldier.o Archer.o Horseman.o TroopList.o

	$(CC) -o $(GAME_NAME) main.cpp TroopList.o Game.o Unit.o AttackUnit.o DefenceUnit.o Soldier.o Archer.o Horseman.o -lSDL2

debug: main.cpp debugGame debugUnit debugAttackUnit debugSoldier debugArcher debugDefenceUnit debugHorseman debugTroopList

	$(CC) -o $(GAME_NAME) main.cpp TroopList.o Game.o Unit.o AttackUnit.o DefenceUnit.o Soldier.o Archer.o Horseman.o -lSDL2 -g

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
	$(CC) -c Archer.cpp -Wall -lSDL2

TroopList.o:
	$(CC) -c TroopList.cpp -Wall

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

clean:
	rm *.o $(GAME_NAME)
