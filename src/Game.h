#include <SDL2/SDL.h>
#include "Archer.h"
class Game{

//--------------Funções
public:
    bool initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    void newRound(){
    		Archer atacante;
    		atacante.spawn(800,600);
    };
    int getIsRunning(){ return _isRunning; };

//--------------Variáveis
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning;

};
