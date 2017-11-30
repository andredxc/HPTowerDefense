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
    uint i, j;
    int killPos;
    int kill;
    int rangedAttackDamage;
    int meleeAttackDamage;
    int projectileIndex=0, archerIndex=0, horsemanIndex=0, soldierIndex=0;
    Projectile projectileBuffer;

    if(_archerList.size() == 0 && _horsemanList.size() == 0){
        _emptyList = true;
    }

    //Atualiza a torre de defesa
    //_defenceUnit.attackClosestUnits(&_archerList, &_horsemanList, &_soldierList, &_projectileList);

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
            //O projetil deve ser excluído das estruturas
            fprintf(stderr, "****** KILL ME PROJECTILE ***** \n");
            addToKillList(i, PROJECTILE);
         }
    }

    //Atualiza os arqueiros
    for(i = 0; i < _archerList.size(); i++){

        fprintf(stderr, "\t\tSou o arqueiro %d\n",i);
        rangedAttackDamage = _archerList.at(i).update(&_defenceUnit);
        fprintf(stderr, "ARCHER HAS %d LIFE\n", _archerList.at(i).getHealth());
        if(_archerList.at(i).getHealth() <= 0){
            fprintf(stderr, "****** KILL ME ARCHER ***** \n");
            //Unidade morta
            addToKillList(i, ARCHER);
            //Atualiza a lista de projéteis em direção ao archer morto
            for(j = 0; j < _projectileList.size(); j++){
                if(_projectileList.at(j).getTarget() == &_archerList.at(i)){
                    addToKillList(j, PROJECTILE);
                }
            }
        }
        else if(rangedAttackDamage > 0){
            //Projétil em direção à torre
            Projectile projectileBuffer(2, rangedAttackDamage, 4, 4, _archerList.at(i).getXPos(), _archerList.at(i).getYPos(), &_defenceUnit);
            _projectileList.push_back(projectileBuffer);
        }
    }

    // Atualiza Horseman
    for (i = 0; i < _horsemanList.size(); i++){
        
        fprintf(stderr, "\t\tSou o Horseman %d\n",i);
        meleeAttackDamage = _horsemanList.at(i).update(&_defenceUnit);
        fprintf(stderr, "HORSEMAN HAS %d LIFE\n", _horsemanList.at(i).getHealth());
        if(_horsemanList.at(i).getHealth() <= 0){
            fprintf(stderr, "****** KILL ME HORSEMAN ***** \n");
            //Unidade morta
            addToKillList(i, HORSEMAN);
            //Atualiza a lista de projéteis em direção ao archer morto
            for(j = 0; j < _projectileList.size(); j++){
                if(_projectileList.at(j).getTarget() == &_horsemanList.at(i)){
                    addToKillList(j, PROJECTILE);
                }
            }
        }             

    }



    // Elimina os objetos dentro da killList
    for(i = 0; i < _killList.size(); i++){

        killPos = _killList.at(i)._pos;
        switch(_killList.at(i)._type){

            case PROJECTILE:{

                 try{   
                    _projectileList.erase(_projectileList.begin() + killPos - projectileIndex); projectileIndex++; break;    
                 }
                catch(const char* e){
                    std::cerr << "Deallocation Error Projectile: " << e << std::endl;
                }
                catch(...){
                    std::cerr << "Unexpected Fatal Deallocation Error Projectile!!" << std::endl;
                }     

            }
            case ARCHER:{
                try{
                    _archerList.erase(_archerList.begin() + killPos - archerIndex); archerIndex++; break;
                }
                catch(const char* e){
                    std::cerr << "Deallocation Error ARCHER: " << e << std::endl;
                }
                catch(...){
                    std::cerr << "Unexpected Fatal Deallocation Error ARCHER!!" << std::endl;
                }                     
            }
            case HORSEMAN:{
                try{
                    _horsemanList.erase(_horsemanList.begin() + killPos - horsemanIndex); horsemanIndex++; break;
                }
                catch(const char* e){
                    std::cerr << "Deallocation Error HORSEMAN: " << e << std::endl;
                }
                catch(...){
                    std::cerr << "Unexpected Fatal Deallocation Error HORSEMAN!!" << std::endl;
                }                     


            }

            default: printf("Fatal internal error deleting object\n");
        }
     }
     _killList.clear();     // Desaloca toda a lista de unidades por matar
}

void Game::addToKillList(int position, UNIT_TYPE unit){

    uint i;
    bool itemFound = false;
    killItem item;

    for(i = 0; i < _killList.size(); i++){
        if(_killList.at(i)._pos == position && _killList.at(i)._type == unit){
            itemFound = true;
        }
    }

    if(!itemFound){
        item._pos = position;
        item._type = unit;
        _killList.push_back(item);
    }
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
    for(i = 0; i < _horsemanList.size(); i++)
    {
        _horsemanList.at(i).render(_renderer, _screenWidth, _screenHeight);
        // fprintf(stderr, "Rendering projectile %d of %ld\n", i+1, _projectileList.size());
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
    for (int i = 0; i < 10 ; ++i)
    {
        try{
            Archer archer;
            Horseman horseman;
           // _archerList.push_back(archer);
            _horsemanList.push_back(horseman);
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
