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
                case SDLK_1:    //Health
                    gamePurchaseUpgrade(game, HEALTH);
                    return;
                case SDLK_2:    //Armour
                    gamePurchaseUpgrade(game, ARMOUR);
                    return;
                case SDLK_3:    //Damage
                    gamePurchaseUpgrade(game, DAMAGE);
                    return;
                case SDLK_4:    //Attack range
                    gamePurchaseUpgrade(game, RANGE);
                    return;
                case SDLK_5:    //Number of targets
                    gamePurchaseUpgrade(game, TARGETS);
                    return;
                case SDLK_6:    //Attack delay
                    gamePurchaseUpgrade(game, DELAY);
                    return;
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
    auto updateProjectile = []( PROJECTILE& P ){
         
        if(!P._isDead){
            projectileUpdate(&P);            
        }
    };
    auto updateArcher = [&game]( UNIT& U ){
        int rangedAttackDamage;
         if(U._currentHealth > 0)
                {
                    rangedAttackDamage = U.updateFunction(&U, &game->_defenceUnit);
                    if(rangedAttackDamage > 0)
                    {
                        // O arqueiro lança um projétil em diração a torre
                        PROJECTILE projectileBuffer = createProjectile(&game->_defenceUnit, game->_defenceUnit._xPos, game->_defenceUnit._yPos, rangedAttackDamage);
            // Aqui devemos criar uma nova lista para inerir o novo projetil 
                        game->_projectileList.push_back(projectileBuffer);
                    }
                }
                else
                {
                    game->_bitCoins += unitGetReward(&U);
                }        

    };    
    auto updateHorseman = [&game]( UNIT& U ){
         if(U._currentHealth > 0)
        {
            U.updateFunction(&U, &game->_defenceUnit);
        }
        else
        {
            game->_bitCoins += unitGetReward(&U);
        }        

    };
    auto updateSoldier = [&game]( UNIT& U ){
        if(U._currentHealth > 0)
        {
            U.updateFunction(&U, &game->_defenceUnit);
        }
        else
        {
            game->_bitCoins += unitGetReward(&U);
        }
    };
   // uint i;
    //int rangedAttackDamage;

    if(game->_archerList.size() == 0 && game->_horsemanList.size() == 0){
        game->_emptyList = true;
    }

    //Atualiza a torre de defesa
    attackClosestUnits(&game->_defenceUnit, &game->_archerList, &game->_horsemanList, &game->_soldierList, &game->_projectileList);

    // Atualiza os projeteis
    std::for_each(game->_projectileList.begin(),game->_projectileList.end(),updateProjectile);

/*
    //Atualiza os projéteis
    for(i = 0; i < game->_projectileList.size(); i++)
    {
        // aqui podemos criar uma funcao lambda para chamar a cada elemento do vector 


        if(!game->_projectileList.at(i)._isDead)
        {
            projectileUpdate(&game->_projectileList.at(i));
        }
    }

*/
    std::for_each(game->_archerList.begin(),game->_archerList.end(),updateArcher);
/*
    //Atualiza os arqueiros
    for(i = 0; i < game->_archerList.size(); i++)
    {
        if(game->_archerList.at(i)._currentHealth > 0)
        {
            rangedAttackDamage = game->_archerList.at(i).updateFunction(&game->_archerList.at(i), &game->_defenceUnit);
            if(rangedAttackDamage > 0)
            {
                printf("Criando projetil \n");
                // O arqueiro lança um projétil em diração a torre
                PROJECTILE projectileBuffer = createProjectile(&game->_defenceUnit, game->_defenceUnit._xPos, game->_defenceUnit._yPos, rangedAttackDamage);
                game->_projectileList.push_back(projectileBuffer);
            }
        }
        else
        {
            game->_bitCoins += unitGetReward(&game->_archerList.at(i));
        }
    }

*/
    std::for_each(game->_horsemanList.begin(),game->_horsemanList.end(),updateHorseman);
/*    // Atualiza os horsemen
    for (i = 0; i < game->_horsemanList.size(); i++)
    {
        if(game->_horsemanList.at(i)._currentHealth > 0)
        {
            game->_horsemanList.at(i).updateFunction(&game->_horsemanList.at(i), &game->_defenceUnit);
        }
        else
        {
            game->_bitCoins += unitGetReward(&game->_horsemanList.at(i));
        }
    }
*/
    std::for_each(game->_soldierList.begin(),game->_soldierList.end(),updateSoldier);
    // Atualiza soldiers
/*    for (i = 0; i < game->_soldierList.size(); i++)
    {
        if(game->_soldierList.at(i)._currentHealth > 0)
        {
            game->_soldierList.at(i).updateFunction(&game->_soldierList.at(i), &game->_defenceUnit);
        }
        else
        {
            game->_bitCoins += unitGetReward(&game->_soldierList.at(i));
        }
    }
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
    // Renderiza a defence unit
    game->_defenceUnit.renderFunction(&game->_defenceUnit, game->_renderer, game->_screenWidth, game->_screenHeight);
    // Renderiza os archers
    for(i = 0; i < game->_archerList.size(); i++)
    {
        if(game->_archerList.at(i)._currentHealth > 0){
            if(!game->_archerList.at(i).renderFunction(&game->_archerList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight))
            {
                // Tenta novamente
                game->_archerList.at(i).renderFunction(&game->_archerList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight);
            }
        }
    }
    // Renderiza os horsemen
    for(i = 0; i < game->_horsemanList.size(); i++)
    {
        if(game->_horsemanList.at(i)._currentHealth > 0){
            if(!game->_horsemanList.at(i).renderFunction(&game->_horsemanList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight))
            {
                // Tenta novamente
                game->_horsemanList.at(i).renderFunction(&game->_horsemanList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight);
            }
        }
    }
    // Renderiza os soldiers
    for(i = 0; i < game->_soldierList.size(); i++)
    {
        if(game->_soldierList.at(i)._currentHealth > 0){
            if(!game->_soldierList.at(i).renderFunction(&game->_soldierList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight))
            {
                // Tenta novamente
                game->_soldierList.at(i).renderFunction(&game->_soldierList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight);
            }
        }
    }
    // Renderiza os projectiles
    for(i = 0; i < game->_projectileList.size(); i++)
    {
        if(!game->_projectileList.at(i)._isDead){
            if(!projectileRender(&game->_projectileList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight))
            {
                // Tenta novamente
                projectileRender(&game->_projectileList.at(i), game->_renderer, game->_screenWidth, game->_screenHeight);
            }
        }
    }
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

    // Remove todos os inimigos e projéteis
    gameClearLists(game);
    // Recupera a vida da torre
    game->_defenceUnit.recoverHealthFunction(&game->_defenceUnit);
    // Coloca archers
    newUnits = rand() % round;
    for (int i = 0; i < round + newUnits; i++)
    {
        UNIT archer = createArcher();
        archer.spawnFunction(&archer, game->_screenWidth, game->_screenHeight);
        game->_archerList.push_back(archer);
    }
    // Coloca horsemen
    newUnits = rand() % round;
    for (int i = 0; i < round + newUnits ; i++)
    {
        UNIT horseman = createHorseman();
        horseman.spawnFunction(&horseman, game->_screenWidth, game->_screenHeight);
        game->_horsemanList.push_back(horseman);
    }
    // Coloca soldiers
    newUnits = rand() % round;
    for (int i = 0; i < round + newUnits ; i++)
    {
        UNIT soldier = createSoldier();
        soldier.spawnFunction(&soldier, game->_screenWidth, game->_screenHeight);
        game->_soldierList.push_back(soldier);
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
        getAttributeLevel(game->_defenceUnit, HEALTH), game->_defenceUnit._currentHealth, game->_defenceUnit._totalHealth, getAttributeUpgradeCost(game->_defenceUnit, HEALTH));
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

/* Escreve uma linha de texto na tela */
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

/* Compra um upgrade */
void gamePurchaseUpgrade(GAME* game, ATTRIBUTE attr)
{
    if(game->_bitCoins >= getAttributeUpgradeCost(game->_defenceUnit, attr)){
        //Tem moedas o suficiente
        game->_bitCoins -= getAttributeUpgradeCost(game->_defenceUnit, attr);
        incAttributeLevel(&game->_defenceUnit, attr);
    }
}

/* Destrói todas as listas de unidades e projéteis */
void gameClearLists(GAME* game)
{
    uint i;

    for(i = 0; i < game->_archerList.size(); i++)
    {
        deleteUnit(&game->_archerList.at(i));
    }
    for(i = 0; i < game->_horsemanList.size(); i++)
    {
        deleteUnit(&game->_horsemanList.at(i));
    }
    for(i = 0; i < game->_projectileList.size(); i++)
    {
        deleteProjectile(&game->_projectileList.at(i));
    }
}

/* Verifica se o round já chegou ao fim */
bool gameEndOfRound(GAME game)
{
    uint i;

    // Verifica a lista de archers
    for(i = 0; i < game._archerList.size(); i++)
    {
        if(game._archerList.at(i)._currentHealth > 0)
        {
            return false;
        }
    }
    // Verifica a lista de horsemen
    for(i = 0; i < game._horsemanList.size(); i++)
    {
        if(game._horsemanList.at(i)._currentHealth > 0)
        {
            return false;
        }
    }
    // Verifica a lista de soldiers
    for(i = 0; i < game._soldierList.size(); i++)
    {
        if(game._soldierList.at(i)._currentHealth > 0)
        {
            return false;
        }
    }
    return true;
}
