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
        flags = SDL_WINDOW_FULLSCREEN | SDL_INIT_AUDIO;
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
    // Inicia a música
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    if(!SDL_LoadWAV(SOUNDTRACK_PATH, &wavSpec, &game->_wavBuffer, &wavLength)){
        fprintf(stderr, "Couldn't load soundtrack\n");
    }
    game->_audioPaused = true;
    game->_deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_QueueAudio(game->_deviceId, game->_wavBuffer, wavLength);
    SDL_PauseAudioDevice(game->_deviceId, 1);
    //Dimensões da tela podem ser alteradas para acomodar os menus
    SDL_GetWindowSize(game->_window, &game->_screenWidth, &game->_screenHeight);
    //Define o tamanho da tela jogável
    game->_textAreaHeight = 140;
    game->_screenHeight = game->_screenHeight - (game->_textAreaHeight + 28);
    //Inicializa variáveis referentes aos textos e a unidade de defesa
    game->_defenceUnit = createDefenceUnit();
    game->_defenceUnit.spawnFunction(&game->_defenceUnit, game->_screenWidth, game->_screenHeight);
    unitSetHealthBar(&game->_defenceUnit, 20, game->_screenHeight+4, game->_screenWidth - 40, 20);
    //Define o tamanho e posici- Tirar as coisas relacionadas a variável _emptyListonamento da barra de vida da torre de defesa
    game->_textAreaY = game->_screenHeight + 28;    //Soma a altura da health bar
    game->_textFont = TTF_OpenFont(FONT_TTF_FILE, 18);
    game->_textColor.r = 255;
    game->_textColor.g = 255;
    game->_textColor.b = 255;
    //Inicializa variáveis do jogo
    game->_isRunning = true;
    game->_bitCoins = 0;
    game->_round = 0;

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
                case SDLK_y:
                    if(gameEndOfGame(*game)){
                        // Trata o botão para começar um novo jogo
                        gameStartNewGame(game);
                    }
                    break;
                case SDLK_n:
                    if(gameEndOfGame(*game)){
                        // Trata o botão para dispensar o novo jogo
                        game->_isRunning = false;
                    }
                    break;
                case SDLK_m:
                    if(game->_audioPaused){
                        SDL_PauseAudioDevice(game->_deviceId, 0);
                        game->_audioPaused = false;
                    }
                    else{
                        SDL_PauseAudioDevice(game->_deviceId, 1);
                        game->_audioPaused = true;
                    }
                    break;
                case SDLK_ESCAPE:
                    game->_isRunning = false;
                    return;
            }
        }
    }
}

std::vector<PROJECTILE> insertList(std::vector<PROJECTILE> list,PROJECTILE newP){

    std::vector<PROJECTILE> newL(list); // Cria um vetor igual ao passdo como parametro
    newL.push_back(newP); // Insere novo projetil
    return newL;
}    
/* Atualiza o renderer que será mostrado na tela */
void gameUpdate(GAME* game)
{
    auto updateProjectile = [](PROJECTILE& proj)
    {
        if(!proj._isDead)
        {
            projectileUpdate(&proj);
        }
    };
    auto updateArcher = [&game](UNIT& archer){
        int rangedAttackDamage;
        if(archer._currentHealth > 0)
        {
            rangedAttackDamage = archer.updateFunction(&archer, &game->_defenceUnit);
            if(rangedAttackDamage > 0)
            {
                // O arqueiro lança um projétil em diração a torre
                // Aqui devemos criar uma nova lista para inerir o novo projetil
                PROJECTILE projectileBuffer = createProjectile(&game->_defenceUnit, archer._xPos, archer._yPos, rangedAttackDamage);

                game->_projectileList = insertList(game->_projectileList,projectileBuffer);
               // game->_projectileList.push_back(projectileBuffer);
            }
            else
            {
                game->_bitCoins += unitGetReward(&archer);
            }
        }
    };
    auto updateHorseman = [&game](UNIT& horseman){
        if(horseman._currentHealth > 0)
        {
            horseman.updateFunction(&horseman, &game->_defenceUnit);
        }
        else
        {
            game->_bitCoins += unitGetReward(&horseman);
        }
    };
    auto updateSoldier = [&game](UNIT& soldier){
        if(soldier._currentHealth > 0)
        {
            soldier.updateFunction(&soldier, &game->_defenceUnit);
        }
        else
        {
            game->_bitCoins += unitGetReward(&soldier);
        }
    };

    //Atualiza a torre de defesa
    attackClosestUnits(&game->_defenceUnit, &game->_archerList, &game->_horsemanList, &game->_soldierList, &game->_projectileList);
    // Atualiza os projéteis
    std::for_each(game->_projectileList.begin(),game->_projectileList.end(),updateProjectile);
    // Atualiza os inimigos
    std::for_each(game->_archerList.begin(),game->_archerList.end(),updateArcher);
    std::for_each(game->_horsemanList.begin(),game->_horsemanList.end(),updateHorseman);
    std::for_each(game->_soldierList.begin(),game->_soldierList.end(),updateSoldier);
}

/* Coloca coisas na tela */
void gameRender(GAME* game)
{
    char roundStr[10];
    auto renderUnit = [&game](UNIT& U){
        if(U._currentHealth > 0){
            if(!U.renderFunction(&U, game->_renderer, game->_screenWidth, game->_screenHeight))
            {
                // Tenta novamente
                U.renderFunction(&U, game->_renderer, game->_screenWidth, game->_screenHeight);
            }
        }
    };
    auto renderProjectile = [&game](PROJECTILE& P){
        if(!P._isDead){
            if(!projectileRender(&P, game->_renderer, game->_screenWidth, game->_screenHeight))
            {
                // Tenta novamente
                projectileRender(&P, game->_renderer, game->_screenWidth, game->_screenHeight);
            }
        }
    };

    SDL_RenderClear(game->_renderer);
    // Renderiza a defence unit
    game->_defenceUnit.renderFunction(&game->_defenceUnit, game->_renderer, game->_screenWidth, game->_screenHeight);
    // Renderiza os inimigos
    std::for_each(game->_archerList.begin(),game->_archerList.end(),renderUnit);
    std::for_each(game->_horsemanList.begin(),game->_horsemanList.end(),renderUnit);
    std::for_each(game->_soldierList.begin(),game->_soldierList.end(),renderUnit);
    // Renderiza os projéteis
    std::for_each(game->_projectileList.begin(),game->_projectileList.end(),renderProjectile);
    // Desenha os dados da torre
    gameDrawStats(game);
    // Verifica se o jogo acabou
    if(gameEndOfGame(*game))
    {
        // Mostra mensagem de fim de jogo
        gameDrawText(game, "YOU LOST", 30, 30);
        gameDrawText(game, "Try again? (y/n)", 30, 50);
    }
    // Escreve a onda atual na tela
    snprintf(roundStr, sizeof(roundStr), "Wave %d", game->_round);
    gameDrawText(game, roundStr, game->_screenWidth-100, 30);
    SDL_RenderPresent(game->_renderer);
}

/* Desaloca coisas */
void gameClean(GAME* game)
{
    SDL_CloseAudioDevice(game->_deviceId);
    SDL_FreeWAV(game->_wavBuffer);
    SDL_DestroyWindow(game->_window);
    SDL_DestroyRenderer(game->_renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::vector<UNIT> createUnitList(int i, UNIT_TYPE unit, int size, GAME* game)
{
	std::vector<UNIT> list;
	if(i < size)
	{
		UNIT newUnit;
		switch(unit)
		{
			case ARCHER:
				newUnit = createArcher();
				break;
			case HORSEMAN:
				newUnit = createHorseman();
				break;
			case SOLDIER:
				newUnit = createSoldier();
				break;
            default:
                fprintf(stderr, "Error, DEFENCE should not be used in this function\n");
		}

		newUnit.spawnFunction(&newUnit, game->_screenWidth, game->_screenHeight);
		i++;
		list = createUnitList(i,unit,size, game);
		list.push_back(newUnit);
	}
	return list;
}

/* Cria as unidades para um novo round */
void gameNewRound(GAME* game)
{
    int newUnits;

    game->_round++;

    // Remove todos os inimigos e projéteis
    gameClearLists(game);
    // Recupera a vida da torre
    game->_defenceUnit.recoverHealthFunction(&game->_defenceUnit);

    // Coloca archers
    newUnits = rand() % game->_round;
    game->_archerList = createUnitList(0, ARCHER, game->_round + newUnits, game);

    //~ for (int i = 0; i < game->_round + newUnits; i++)
    //~ {
        //~ UNIT archer = createArcher();
        //~ archer.spawnFunction(&archer, game->_screenWidth, game->_screenHeight);
        //~ game->_archerList.push_back(archer);
    //~ }
    // Coloca horsemen

    newUnits = rand() % game->_round;
    game->_horsemanList = createUnitList(0, HORSEMAN, game->_round + newUnits, game);
    //~ for (int i = 0; i < game->_round + newUnits ; i++)
    //~ {
        //~ UNIT horseman = createHorseman();
        //~ horseman.spawnFunction(&horseman, game->_screenWidth, game->_screenHeight);
        //~ game->_horsemanList.push_back(horseman);
    //~ }
    // Coloca soldiers
    newUnits = rand() % game->_round;
    game->_soldierList = createUnitList(0, SOLDIER, game->_round + newUnits, game);
    //~ for (int i = 0; i < game->_round + newUnits ; i++)
    //~ {
        //~ UNIT soldier = createSoldier();
        //~ soldier.spawnFunction(&soldier, game->_screenWidth, game->_screenHeight);
        //~ game->_soldierList.push_back(soldier);
    //~ }
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
    // AQUI PODEMOS COLOCAR FUNCOES LAMBDA
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

    game->_archerList.clear();
    game->_horsemanList.clear();
    game->_soldierList.clear();
    game->_projectileList.clear();
}

// AQUI PODEMOS TER UMA FUNCAO PURA
/* Verifica se o round já chegou ao fim */
__attribute__((pure)) bool gameEndOfRound(GAME game)
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
// AQUI PODEMOS TER UMA FUNCAO PURA
/* Verifica se o jogo já chegou ao fim */
__attribute__((pure)) bool gameEndOfGame(GAME game)
{
    if(game._defenceUnit._currentHealth > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Começa um novo jogo */
void gameStartNewGame(GAME* game)
{
    game->_defenceUnit = createDefenceUnit();
    game->_defenceUnit.spawnFunction(&game->_defenceUnit, game->_screenWidth, game->_screenHeight);
    unitSetHealthBar(&game->_defenceUnit, 20, game->_screenHeight+4, game->_screenWidth - 40, 20);
    game->_bitCoins = 0;
    game->_round = 0;
    gameClearLists(game);
}
