#include "Game.h"
#include "Projectile.h"

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
    switch (event.type)
    {
        case SDL_QUIT:
            fprintf(stderr, "SDL_QUIT\n");
            _isRunning = false;
            break;
        default:
            break;
    }
}

/*
*   Atualiza o renderer que será mostrado na tela
*/
void Game::update()
{
    uint i;

    if(_archerList.size() == 0){
        _emptyList = true;
    }

    for(i = 0; i < _archerList.size(); i++){
        _archerList.at(i).update(&_defenceUnit);
    }
}

/*
*   Coloca coisas na tela
*/
void Game::render()
{
    int i;


    SDL_RenderClear(_renderer);
    // _archerList.at(0).render(_renderer, _screenWidth, _screenHeight);

    _defenceUnit.render(_renderer, _screenWidth, _screenHeight);
    //Testando projectile
    // Projectile projectile(10, 10, 4, 4, 90, 90, NULL);
    // projectile.render(_renderer, _screenWidth, _screenHeight);

    for(i = 0; i < _archerList.size(); i++)
    {
        // fprintf(stderr, "Rendering archer %d of %d\n", i+1, _archerList.size());
        _archerList.at(i).render(_renderer, _screenWidth, _screenHeight);
    }

    SDL_RenderPresent(_renderer);
}

/*
*   Desaloca coisas
*/
void Game::clean()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Game::newRound()
{
        // Insere elementos nas listas 1 de cada tipo
        // Os parametro devem aumentar progressivamente de algum jeito
        Archer archer;
        archer.setHealth(150);
        archer.setArmour(50);
        _archerList.push_back(archer);

        _emptyList = false; // Quando a torre mata um bixinho, temos que chamar o metodo que atualiza a lista -> remover (implementar) e setar para true
};
int Game::getIsRunning(){ return _isRunning; };
int Game::getListStatus(){ return _emptyList; };
