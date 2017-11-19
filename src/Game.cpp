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
    SDL_RenderClear(_renderer);
    
    SDL_RenderPresent(_renderer);
}

/*
*   Desaloca coisas
*/
void Game::clean(){

    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}
