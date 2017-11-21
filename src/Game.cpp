#include "Game.h"

/*
*   Inicializa SDL_Window, SDL_Renderer e tal
*/
bool Game::initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen){

    int flags = 0;

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error \"%s\" initializing SDL\n", SDL_GetError());
        return false;
    }

    _window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
    if(!_window){
        printf("Error creating window\n");
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if(!_renderer){
        printf("Error creating renderer\n");
        SDL_DestroyWindow(_window);
        return false;
    }
    _isRunning = true;
    _emptyList = true;
    //Dimensões da tela podem ser alteradas para acomodar os menus
    SDL_GetWindowSize(_window, &_screenWidth, &_screenHeight);
    return true;
}

/*
*   Handler para eventos de teclado e afins
*/
void Game::handleEvents(){

    SDL_Event event;

    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            _isRunning = false;
            break;
        default:
            break;
    }
}

/*
*   Atualiza o renderer que será mostrado na tela
*/
void Game::update(){
}

/*
*   Coloca coisas na tela
*/
void Game::render(){

    int i;

    SDL_RenderClear(_renderer);
    for(i = 0; i < _archerList.size(); i++)
    {
        fprintf(stderr, "Rendering archer %d of %d\n", i+1, _archerList.size());
        _archerList.at(i).render(_renderer, _screenWidth, _screenHeight);
    }

    SDL_RenderPresent(_renderer);
}

/*
*   Desaloca coisas
*/
void Game::clean(){

    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Game::newRound(){
        // Insere elementos nas listas 1 de cada tipo
        // Os parametro devem aumentar progressivamente de algum jeito
        Archer archer(_renderer);
        archer.spawn(_screenWidth, _screenHeight);
        archer.setHealth(150);
        archer.setArmour(50);
        archer.setDps(15);
        archer.setRangedAttack(12);
        archer.setMeleeAttack(0);
        archer.setAttackRange(50);
        _archerList.append(archer);

        _emptyList = false; // Quando a torre mata um bixinho, temos que chamar o metodo que atualiza a lista -> remover (implementar) e setar para true
};
int Game::getIsRunning(){ return _isRunning; };
int Game::getListStatus(){ return _emptyList ; };
