#include "Game.h"
#include "Projectile.h"
#include <stdexcept>

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
    //Define o tamanho e posicionamento da barra de vida da torre de defesa
    //20 de padding nas laterais e 4 em cima e embaixo
    _screenHeight -= 28;
    _defenceUnit.setHealthBar(20, _screenHeight+4, _screenWidth - 40, 20);

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
    int killPos;
    int kill;
    int rangedAttackDamage;
    Projectile projectileBuffer;
    if(_archerList.size() == 0){
        _emptyList = true;
    }
    //Atualiza os projéteis
    for(i = 0; i < _projectileList.size(); i++){
        fprintf(stderr, "\tSou o projetil %d\n",i);    

         try{   
            kill = _projectileList.at(i).update();
        }
        catch (const std::out_of_range& oor) {
                std::cerr << "[PROJECTILE] Out of Range error: " << oor.what() << '\n';
        }

        if(kill){    
            fprintf(stderr, "****** KILL ME PROJECTILE ***** \n");
            killItem item;
            item._pos = i;
            item._type = PROJECTILE;   
            _killList.push_back(item);
         }       
    }
    //Atualiza os arqueiros
    for(i = 0; i < _archerList.size(); i++){
        rangedAttackDamage = _archerList.at(i).update(&_defenceUnit);
        fprintf(stderr, "\t\tSou o arqueiro %d\n",i);    
        if(rangedAttackDamage > 0){
            //Projétil não vazio em direção à torre
            Projectile projectileBuffer(2, rangedAttackDamage, 4, 4, _archerList.at(i).getXPos(), _archerList.at(i).getYPos(), &_defenceUnit);
            _projectileList.push_back(projectileBuffer);
        }
        else
            if (rangedAttackDamage == -1) // Inserir na killList
             {
                fprintf(stderr, "****** KILL ME ARCHER ***** \n");
                killItem item;
                item._pos = i;
                item._type = ARCHER;   
                _killList.push_back(item);
             } 

    }

    // Elimina os objetos com _health == 0 e os projéteis que já explodiram
    for(i = 0; i < _killList.size(); i++){
        killPos = _killList.at(i)._pos;
        //printf("KILLPOS: %d\n",killPos);
        //printf("LIST SIZE: %d\n",_killList.size() );    

        switch(_killList.at(i)._type){

            case PROJECTILE: _projectileList.erase(_projectileList.begin() + killPos); break;      
            case ARCHER:_archerList.erase(_archerList.begin() + killPos);  break;
            default: printf("Fatal internal error deleting object\n");
        }
     }
     _killList.clear();     // Desaloca toda a lista de unidades por matar
}

/*
*   Coloca coisas na tela
*/
void Game::render()
{
    uint i;


    SDL_RenderClear(_renderer);
    // _archerList.at(0).render(_renderer, _screenWidth, _screenHeight);

    _defenceUnit.render(_renderer, _screenWidth, _screenHeight);
    //Testando projectile
    // Projectile projectile(10, 10, 4, 4, 90, 90, NULL);
    // projectile.render(_renderer, _screenWidth, _screenHeight);


    for(i = 0; i < _archerList.size(); i++)
    {
        _archerList.at(i).render(_renderer, _screenWidth, _screenHeight);
        // fprintf(stderr, "Rendering archer %d of %ld\n", i+1, _archerList.size());
    }
    for(i = 0; i < _projectileList.size(); i++)
    {
        _projectileList.at(i).render(_renderer, _screenWidth, _screenHeight);
        // fprintf(stderr, "Rendering projectile %d of %ld\n", i+1, _projectileList.size());
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
    for (int i = 0; i < 1 ; ++i)
    {
        try{
            Archer archer;
            archer.setHealth(150);
            archer.setArmour(50);
            _archerList.push_back(archer);            
        }
        catch(const char* e){
             std::cerr << "Erro: " << e << std::endl;   
        }
        catch(...){
            std::cerr << "Unexpected Fatal Error !!" << std::endl;
        }    
    }

        _emptyList = false; // Quando a torre mata um bixinho, temos que chamar o metodo que atualiza a lista -> remover (implementar) e setar para true
};
int Game::getIsRunning(){ return _isRunning; };
int Game::getListStatus(){ return _emptyList; };
