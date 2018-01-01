#include <stdexcept>
#include <time.h>
#include <SDL2/SDL_image.h>
#include "Projectile.h"
#include "Game.h"

/* Inicializa SDL_Window, SDL_Renderer e tudo mais */
bool gameInitialize(GAME* game, const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
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
    //Inicializa variáveis referentes aos textos e a unidade de defesa
    game->_defenceUnit = createDefenceUnit();
    game->_defenceUnit.spawnFunction(&game->_defenceUnit, game->_screenWidth, game->_screenHeight);
    unitSetHealthBar(&game->_defenceUnit, 20, game->_screenHeight+4, game->_screenWidth - 40, 20);
    //Define o tamanho e posicionamento da barra de vida da torre de defesa
    game->_textAreaY = game->_screenHeight + 28;    //Soma a altura da health bar
    game->_textFont = TTF_OpenFont(FONT_TTF_FILE, 18);
    game->_textColor.r = 255;
    game->_textColor.g = 255;
    game->_textColor.b = 255;

    return true;
}

/* Handler para eventos de teclado e afins */
void gameHandleEvents(GAME* game)
{
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

/* Atualiza o renderer que será mostrado na tela */
void gameUpdate(GAME* game)
{
    uint i;

    if(game->_archerList.size() == 0 && game->_horsemanList.size() == 0){
        game->_emptyList = true;
    }

    //Atualiza a torre de defesa
    // TODO: Fazer isso funcionar
    //attackClosestUnits(game->_defenceUnit, &game->_archerList, &game->_horsemanList, &game->_soldierList, &game->_projectileList);

    //Atualiza os projéteis
    /*
    for(i = 0; i < game->_projectileList.size(); i++){

        try{
            kill = game->_projectileList.at(i).update();
        }
        catch (const std::out_of_range& oor) {
            printf("[PROJECTILE] Out of Range error: %s\n", oor.what());
        }

        if(kill){
            //O projetil deve ser excluído das estruturas
            gameAddToKillList(&game->_killList, i, PROJECTILE);
         }
    }
    */

    //Atualiza os arqueiros
    /*
    for(i = 0; i < game->_archerList.size(); i++){

        rangedAttackDamage = game->_archerList.at(i).update(&game->_defenceUnit);
        if(game->_archerList.at(i).getHealth() <= 0){
            //Unidade morta
            game->_bitCoins += game->_archerList.at(i).getReward();
            gameAddToKillList(&game->_killList, i, ARCHER);
            //Atualiza a lista de projéteis em direção ao archer morto
            for(j = 0; j < game->_projectileList.size(); j++){
                if(game->_projectileList.at(j).getTarget() == &game->_archerList.at(i)){
                    gameAddToKillList(&game->_killList, j, PROJECTILE);
                }
            }
        }
        else if(rangedAttackDamage > 0){
            //Projétil em direção à torre
            Projectile projectileBuffer(2, rangedAttackDamage, 4, 4, game->_archerList.at(i).getXPos(), game->_archerList.at(i).getYPos(), &game->_defenceUnit);
            game->_projectileList.push_back(projectileBuffer);
        }
    }
    */

    // Atualiza Horseman
    for (i = 0; i < game->_horsemanList.size(); i++){

        game->_horsemanList.at(i).updateFunction(&game->_horsemanList.at(i), &game->_defenceUnit);
        if(game->_horsemanList.at(i)._currentHealth <= 0){
            game->_bitCoins += game->_horsemanList.at(i)._reward;
            //Unidade morta
            gameAddToKillList(&game->_killList, i, HORSEMAN);
            //Atualiza a lista de projéteis em direção ao horseman morto
            /*
            for(j = 0; j < game->_projectileList.size(); j++){
                if(game->_projectileList.at(j).getTarget() == &game->_horsemanList.at(i)){
                    gameAddToKillList(&game->_killList, j, PROJECTILE);
                }
            }
            */
        }
    }

    // Elimina os objetos dentro da killList
    /*
    for(i = 0; i < game->_killList.size(); i++){

        killPos = game->_killList.at(i)._pos;
        switch(game->_killList.at(i)._type){

            case PROJECTILE:{

                try{
                    game->_projectileList.erase(game->_projectileList.begin() + killPos - projectileIndex); projectileIndex++; break;
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
                    game->_archerList.erase(game->_archerList.begin() + killPos - archerIndex); archerIndex++; break;
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
                    game->_horsemanList.erase(game->_horsemanList.begin() + killPos - horsemanIndex); horsemanIndex++; break;
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

     game->_killList.clear();     // Desaloca toda a lista de unidades por matar
     */
}

/* Adiciona um elemento a lista e unidades que devem ser desalocadas */
void gameAddToKillList(std::vector<KILL_ITEM>* killList, int position, UNIT_TYPE unit)
{
    uint i;
    bool itemFound = false;
    KILL_ITEM item;

    for(i = 0; i < killList->size(); i++){
        // Verifica se o elemento já existe
        if(killList->at(i)._pos == position && killList->at(i)._type == unit){
            itemFound = true;
        }
    }

    if(!itemFound){
        // Adiciona um nodo não existente
        item._pos = position;
        item._type = unit;
        killList->push_back(item);
    }
}

/* Coloca coisas na tela */
void gameRender(GAME* game)
{
    uint i;

    SDL_RenderClear(game->_renderer);

    game->_defenceUnit.renderFunction(&game->_defenceUnit, game->_renderer, game->_screenWidth, game->_screenHeight);

    /*
    for(i = 0; i < _archerList.size(); i++)
    {
        if(!_archerList.at(i).render(_renderer, _screenWidth, _screenHeight))
        {
            // Tenta novamente
            _archerList.at(i).render(_renderer, _screenWidth, _screenHeight);
        }
    }
    */
    for(i = 0; i < game->_horsemanList.size(); i++)
    {
        if(!game->_horsemanList.at(i).renderFunction(&game->_horsemanList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight))
        {
            // Tenta novamente
            game->_horsemanList.at(i).renderFunction(&game->_horsemanList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight);
        }
    }

    /*
    for(i = 0; i < _projectileList.size(); i++)
    {
        if(!_projectileList.at(i).render(_renderer, _screenWidth, _screenHeight))
        {
            // Tenta novamente
            _projectileList.at(i).render(_renderer, _screenWidth, _screenHeight);
        }
    }
    */
    gameDrawStats(game);

    SDL_RenderPresent(game->_renderer);
}

/* Desaloca coisas */
void gameClean(GAME* game)
{
    SDL_DestroyWindow(game->_window);
    SDL_DestroyRenderer(game->_renderer);
}

/* Cria as unidades para um novo round */
void gameNewRound(GAME* game)
{
    static int round = 0;
    round = round +1;
    int newUnits;

    newUnits = rand() % round;
    game->_defenceUnit.recoverHealthFunction(&game->_defenceUnit);
    for (int i = 0; i < round + newUnits; i++)
    {
        try{
            UNIT archer = createArcher();
            archer.spawnFunction(&archer, game->_screenWidth, game->_screenHeight);
            game->_archerList.push_back(archer);
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
            UNIT horseman = createHorseman();
            horseman.spawnFunction(&horseman, game->_screenWidth, game->_screenHeight);
            game->_horsemanList.push_back(horseman);
        }
        catch(const char* e){
             printf("Erro: %s\n", e);
        }
        catch(...){
            printf("Unexpected Fatal Error !!\n");
        }
    }

    game->_emptyList = false;
};

/* Desenha os textos referentes aos upgrades */
void gameDrawStats(GAME* game)
{
    char text[256];

    if(!game->_textFont){
        printf("Error opening text font\n");
        return;
    }
    //Escreve os atributos na tela
    snprintf(text, sizeof(text), "(1) Health (level %d): %d/%d [Upgrade: %d bitcoins]",
        getAttributeLevel(game->_defenceUnit, HEALTH), game->_defenceUnit._totalHealth, game->_defenceUnit._totalHealth, getAttributeUpgradeCost(game->_defenceUnit, HEALTH));
    gameDrawText(game, text, 5, game->_textAreaY + 5);
    snprintf(text, sizeof(text), "(2) Armour (level %d): %d [Upgrade: %d bitcoins]",
        getAttributeLevel(game->_defenceUnit, ARMOUR), game->_defenceUnit._armour, getAttributeUpgradeCost(game->_defenceUnit, ARMOUR));
    gameDrawText(game, text, 5, game->_textAreaY + 25);
    snprintf(text, sizeof(text), "(3) Damage (level %d): %d [Upgrade: %d bitcoins]",
        getAttributeLevel(game->_defenceUnit, DAMAGE), game->_defenceUnit._rangedDamage, getAttributeUpgradeCost(game->_defenceUnit, DAMAGE));
    gameDrawText(game, text, 5, game->_textAreaY + 45);
    snprintf(text, sizeof(text), "(4) AttackRange (level %d): %d [Upgrade: %d bitcoins]",
        getAttributeLevel(game->_defenceUnit, RANGE), game->_defenceUnit._attackRange, getAttributeUpgradeCost(game->_defenceUnit, RANGE));
    gameDrawText(game, text, 5, game->_textAreaY + 65);
    snprintf(text, sizeof(text), "(5) Number of targets (level %d): %d [Upgrade: %d bitcoins]",
        getAttributeLevel(game->_defenceUnit, TARGETS), game->_defenceUnit._numberOfTargets, getAttributeUpgradeCost(game->_defenceUnit, TARGETS));
    gameDrawText(game, text, 5, game->_textAreaY + 85);
    snprintf(text, sizeof(text), "(6) Attack Delay (level %d): %d ms [Upgrade: %d bitcoins]",
        getAttributeLevel(game->_defenceUnit, DELAY), game->_defenceUnit._attackDelay, getAttributeUpgradeCost(game->_defenceUnit, DELAY));
    gameDrawText(game, text, 5, game->_textAreaY + 105);
    //Escreve o número de bitcoins
    snprintf(text, sizeof(text), "BitCoins");
    gameDrawText(game, text, game->_screenWidth - 180,  game->_textAreaY + 10);
    snprintf(text, sizeof(text), "%d", game->_bitCoins);
    gameDrawText(game, text, game->_screenWidth - 140,  game->_textAreaY + 30);

}

bool gameDrawText(GAME* game, const char* text, int xPos, int yPos)
{
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect destRect;

    if(!game->_textFont){
        printf("Error opening text font\n");
        return false;
    }
    //Escreve vida na tela
    textSurface = TTF_RenderUTF8_Blended(game->_textFont, text, game->_textColor);
    textTexture = SDL_CreateTextureFromSurface(game->_renderer, textSurface);
    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = textSurface->w;
    destRect.h = textSurface->h;
    SDL_RenderCopy(game->_renderer, textTexture, NULL, &destRect);
    return true;
}

void gamePurchaseUpgrade(GAME* game, ATTRIBUTE attr)
{
    if(game->_bitCoins >= getAttributeUpgradeCost(game->_defenceUnit, attr)){
        //Tem moedas o suficiente
        game->_bitCoins -= getAttributeUpgradeCost(game->_defenceUnit, attr);
        incAttributeLevel(&game->_defenceUnit, attr);
    }
}
