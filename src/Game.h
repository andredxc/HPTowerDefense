#ifndef X_Game_h
#define X_Game_h

#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Archer.h"
//#include "Soldier.h"
#include "Horseman.h"

template <class TipoGenerico>
class troopList {
private:
  TipoGenerico *Filaptr;
  int maxLen;
  int fim;

public:
    troopList() {
      Filaptr = new TipoGenerico [100];
      maxLen = 99;
      fim = -1;
    };

    troopList(int size) {
      Filaptr = new TipoGenerico [size];
      maxLen = size - 1;
      fim = -1;
    };


    ~troopList(){
      delete Filaptr;
    };

    void insere(TipoGenerico number){
    if(fim == maxLen){
        std::cerr << "Fila llena" << std::endl;
    }
    else{
      fim = fim +1 ;
      Filaptr[fim] = number;
      }
    };

    void remove() {
    if(fim == -1){
    	std::cerr << "Fila vazia" << std::endl;
    }
    else{
    	fim = fim -1;
    }
    };

    int ultimo() {
      if (vazio()){
        std::cerr << "Fila vazia" << std::endl;
      }else{
        return Filaptr[fim];
      }
    };

    int vazio() {
      return fim == -1;
    };
     void imprime(){
    	int i =0;
    	for(i=0;i<=fim;i++){
    		//printf("%d\n",i);
    		printf("pos[%d]:%u\n",i,Filaptr[i].getHealth());
    		}
    	};
};


class Game{

//--------------Funções
public:

	// criar 3e listas -> utilizar template cada uma do tipo correspondente ao bixinho que tem tamanho maximo 100
    bool initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

	troopList<Archer> archerList;
	troopList<Horseman> horsemanList;
//	troopList<Soldier> soldierList;

    void newRound(){
    		// Insere elementos nas listas 1 de cada tipo
    		// Os parametro devem aumentar progressivamente de algum jeito
    		Archer archer;
    		archer.spawn();
    		archer.setHealth(150);
    		archer.setArmour(50);
    		archer.setDps(15);
    		archer.setRangedAttack(12);
    		archer.setMeleeAttack(0);
    		archer.setAttackRange(50);

 			archerList.insere(archer);
 			archerList.imprime();

    		_emptyList = false; // Quando a torre mata um bixinho, temos que chamar o metodo que atualiza a lista -> remover (implementar) e setar para true
    };
    int getIsRunning(){ return _isRunning; };
    int getListStatus(){ return _emptyList ; };

//--------------Variáveis
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning;
    bool _emptyList; // Variavel para controlar os rounds
    int _troops;	// Bixinhos que estão ativos na rodada
};
#endif
