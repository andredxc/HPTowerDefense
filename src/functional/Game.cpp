#include <stdexcept>
#include <time.h>
#include <SDL2/SDL_image.h>
#include "Projectile.h"
#include "Game.h"

/*
*   Inicializa SDL_Window, SDL_Renderer e tal
*/
bool gameInitialize(GAME* game, const char* title, int xPos, int yPos, int width, int height, bool fullscreen){

    int flags = 0;
    srand (time(NULL));

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error \"%s\" initializing SDL\n", SDL_GetError());
        return false;
    }
    IMG_Init(0);
    if(TTF_Init() == -1){
        fprintf(stderr, "Error \"%s\" initializing TTF\n", SDL_GetError());
    }

    game->_window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
    if(!game->_window){
        printf("Error creating window\n");
        return false;
    }

    game->_renderer = SDL_CreateRenderer(game->_window, -1, 0);
    if(!game->_renderer){
        printf("Error creating renderer\n");
        SDL_DestroyWindow(game->_window);
        return false;
    }
    game->_isRunning = true;
    game->_emptyList = true;
    game->_bitCoins = 0;
    //Dimensões da tela podem ser alteradas para acomodar os menus
    SDL_GetWindowSize(game->_window, &game->_screenWidth, &game->_screenHeight);
    //Define o tamanho da tela jogável
    game->_textAreaHeight = 140;
    game->_screenHeight = game->_screenHeight - (game->_textAreaHeight + 28);
    //Inicializa variáveis referentes aos textos
    // TODO: definir health bar
    //game->_defenceUnit.setHealthBar(20, game->_screenHeight+4, game->_screenWidth - 40, 20);
    //Define o tamanho e posicionamento da barra de vida da torre de defesa
    game->_textAreaY = game->_screenHeight + 28;    //Soma a altura da health bar
    game->_textFont = TTF_OpenFont(FONT_TTF_FILE, 18);
    game->_textColor.r = 255;
    game->_textColor.g = 255;
    game->_textColor.b = 255;
    //Inicializa a torre de defesa
    

    return true;
}

/*
*   Handler para eventos de teclado e afins
*/
void gameHandleEvents(GAME* game){

    SDL_Event event;

    while(1){

        if(SDL_PollEvent(&event) == 0){
            return;
        }

        if(event.type == SDL_QUIT){
            game->_isRunning = false;
            return;
        }
        else if(event.type == SDL_KEYDOWN){

            switch(event.key.keysym.sym){
                /*
                case SDLK_1:    //Health
                    purchaseUpgrade(HEALTH);
                    return;
                case SDLK_2:    //Armour
                    purchaseUpgrade(ARMOUR);
                    return;
                case SDLK_3:    //Damage
                    purchaseUpgrade(DAMAGE);
                    return;
                case SDLK_4:    //Attack range
                    purchaseUpgrade(RANGE);
                    return;
                case SDLK_5:    //Number of targets
                    purchaseUpgrade(TARGETS);
                    return;
                case SDLK_6:    //Attack delay
                    purchaseUpgrade(DELAY);
                    return;
                    */
                case SDLK_ESCAPE:
                    game->_isRunning = false;
                    return;
            }
        }
    }
}

/*
*   Atualiza o renderer que será mostrado na tela
*/
/*
void gameUpdate()
{
    uint i, j;
    int killPos;
    int kill;
    int rangedAttackDamage;
    int projectileIndex=0, archerIndex=0, horsemanIndex=0, soldierIndex=0;
    Projectile projectileBuffer;

    if(_archerList.size() == 0 && _horsemanList.size() == 0){
        _emptyList = true;
    }

    //Atualiza a torre de defesa
    _defenceUnit.attackClosestUnits(&_archerList, &_horsemanList, &_soldierList, &_projectileList);

    //Atualiza os projéteis
    for(i = 0; i < _projectileList.size(); i++){

        // fprintf(stderr, "\tSou o projetil %d\n",i);
        try{
            kill = _projectileList.at(i).update();
        }
        catch (const std::out_of_range& oor) {
            printf("[PROJECTILE] Out of Range error: %s\n", oor.what());
        }

        if(kill){
            //O projetil deve ser excluído das estruturas
            addToKillList(i, PROJECTILE);
         }
    }

    //Atualiza os arqueiros
    for(i = 0; i < _archerList.size(); i++){

        rangedAttackDamage = _archerList.at(i).update(&_defenceUnit);
        if(_archerList.at(i).getHealth() <= 0){
            //Unidade morta
            _bitCoins += _archerList.at(i).getReward();
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

        _horsemanList.at(i).update(&_defenceUnit);
        if(_horsemanList.at(i).getHealth() <= 0){
            _bitCoins += _horsemanList.at(i).getReward();
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
                    printf("Deallocation Error Projectile: %s\n", e);
                }
                catch(...){
                    printf("Unexpected Fatal Deallocation Error Projectile!!\n");
                }
            }
            case ARCHER:{
                try{
                    _archerList.erase(_archerList.begin() + killPos - archerIndex); archerIndex++; break;
                }
                catch(const char* e){
                    printf("Deallocation Error ARCHER: %s\n", e);
                }
                catch(...){
                    printf("Unexpected Fatal Deallocation Error ARCHER!!\n");
                }
            }
            case HORSEMAN:{
                try{
                    _horsemanList.erase(_horsemanList.begin() + killPos - horsemanIndex); horsemanIndex++; break;
                }
                catch(const char* e){
                    printf("Deallocation Error HORSEMAN: %s\n", e);
                }
                catch(...){
                    printf("Unexpected Fatal Deallocation Error HORSEMAN!!\n");
                }
            }
            default: printf("Fatal internal error deleting object\n");
        }
     }
     _killList.clear();     // Desaloca toda a lista de unidades por matar
}
*/

/*
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
*/

/*
*   Coloca coisas na tela
*/
/*
void Game::render()
{
    uint i;

    SDL_RenderClear(_renderer);

    _defenceUnit.render(_renderer, _screenWidth, _screenHeight);

    for(i = 0; i < _archerList.size(); i++)
    {
        if(!_archerList.at(i).render(_renderer, _screenWidth, _screenHeight)){
            // Tenta novamente
            _archerList.at(i).render(_renderer, _screenWidth, _screenHeight);
        }
    }
    for(i = 0; i < _horsemanList.size(); i++)
    {
        if(!_horsemanList.at(i).render(_renderer, _screenWidth, _screenHeight)){
            // Tenta novamente
            _horsemanList.at(i).render(_renderer, _screenWidth, _screenHeight);
        }
    }

    for(i = 0; i < _projectileList.size(); i++)
    {
        if(!_projectileList.at(i).render(_renderer, _screenWidth, _screenHeight)){
            // Tenta novamente
            _projectileList.at(i).render(_renderer, _screenWidth, _screenHeight);
        }
    }
    drawStats();

    SDL_RenderPresent(_renderer);
}
*/

/*
*   Desaloca coisas
*/
/*
void Game::clean()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Game::newRound()
{
    static int round = 0;
    round = round +1;
    int newUnits;

    newUnits = rand() % round;
    _defenceUnit.recoverHealth();
        //printf("Round:%d\n",round );
       // Insere elementos nas listas 1 de cada tipo
        // Os parametro devem aumentar progressivamente de algum jeito
    for (int i = 0; i < round + newUnits; i++)
    {
        try{
            Archer archer;
            // Horseman horseman;
            // Soldier soldier;
            _archerList.push_back(archer);
        //    _horsemanList.push_back(horseman);
        //    _soldierList.push_back(soldier);
        }
        catch(const char* e){
             printf("Erro: %s\n", e);
        }
        catch(...){
            printf("Unexpected Fatal Error !!\n");
        }
    }
    newUnits = rand() % round;
    for (int i = 0; i < round + newUnits ; i++)
    {
        try{
       //     Archer archer;
            Horseman horseman;
         //   Soldier soldier;
           // _archerList.push_back(archer);
            _horsemanList.push_back(horseman);
            //_soldierList.push_back(soldier);
        }
        catch(const char* e){
             printf("Erro: %s\n", e);
        }
        catch(...){
            printf("Unexpected Fatal Error !!\n");
        }
    }

        _emptyList = false; // Quando a torre mata um bixinho, temos que chamar o metodo que atualiza a lista -> remover (implementar) e setar para true
};

void Game::drawStats()
{
    char text[256];

    if(!_textFont){
        printf("Error opening text font\n");
        return;
    }
    //Escreve os atributos na tela
    snprintf(text, sizeof(text), "(1) Health (level %d): %d/%d [Upgrade: %d bitcoins]",
        _defenceUnit.getAttributeLevel(HEALTH), _defenceUnit.getHealth(), _defenceUnit.getTotalHealth(), _defenceUnit.getAttributeUpgradeCost(HEALTH));
    drawText(text, 5, _textAreaY + 5);
    snprintf(text, sizeof(text), "(2) Armour (level %d): %d [Upgrade: %d bitcoins]",
        _defenceUnit.getAttributeLevel(ARMOUR), _defenceUnit.getArmour(), _defenceUnit.getAttributeUpgradeCost(ARMOUR));
    drawText(text, 5, _textAreaY + 25);
    snprintf(text, sizeof(text), "(3) Damage (level %d): %d [Upgrade: %d bitcoins]",
        _defenceUnit.getAttributeLevel(DAMAGE), _defenceUnit.getRangedDamage(), _defenceUnit.getAttributeUpgradeCost(DAMAGE));
    drawText(text, 5, _textAreaY + 45);
    snprintf(text, sizeof(text), "(4) AttackRange (level %d): %d [Upgrade: %d bitcoins]",
        _defenceUnit.getAttributeLevel(RANGE), _defenceUnit.getAttackRange(), _defenceUnit.getAttributeUpgradeCost(RANGE));
    drawText(text, 5, _textAreaY + 65);
    snprintf(text, sizeof(text), "(5) Number of targets (level %d): %d [Upgrade: %d bitcoins]",
        _defenceUnit.getAttributeLevel(TARGETS), _defenceUnit.getNumberOfTargets(), _defenceUnit.getAttributeUpgradeCost(TARGETS));
    drawText(text, 5, _textAreaY + 85);
    snprintf(text, sizeof(text), "(6) Attack Delay (level %d): %d ms [Upgrade: %d bitcoins]",
        _defenceUnit.getAttributeLevel(DELAY), _defenceUnit.getAttackDelay(), _defenceUnit.getAttributeUpgradeCost(DELAY));
    drawText(text, 5, _textAreaY + 105);
    //Escreve o número de bitcoins
    snprintf(text, sizeof(text), "BitCoins");
    drawText(text, _screenWidth - 180,  _textAreaY + 10);
    snprintf(text, sizeof(text), "%d", _bitCoins);
    drawText(text, _screenWidth - 140,  _textAreaY + 30);

}

bool Game::drawText(const char* text, int xPos, int yPos)
{
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect destRect;

    if(!_textFont){
        printf("Error opening text font\n");
        return false;
    }
    //Escreve vida na tela
    textSurface = TTF_RenderUTF8_Blended(_textFont, text, _textColor);
    textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = textSurface->w;
    destRect.h = textSurface->h;
    SDL_RenderCopy(_renderer, textTexture, NULL, &destRect);
    return true;
}

void Game::purchaseUpgrade(ATTRIBUTE attr)
{
    if(_bitCoins >= _defenceUnit.getAttributeUpgradeCost(attr)){
        //Tem moedas o suficiente
        _bitCoins -= _defenceUnit.getAttributeUpgradeCost(attr);
        _defenceUnit.incAttributeLevel(attr);
    }
}

int Game::getIsRunning(){ return _isRunning; };
int Game::getListStatus(){ return _emptyList; };
*/
