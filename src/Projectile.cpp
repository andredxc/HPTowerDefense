#include "Projectile.h"

#include <SDL2/SDL_image.h>

Projectile::Projectile()
{
    _speed = -1;
    _damage = -1;
    _xPos = -1;
    _yPos = -1;
    _destXPos = -1;
    _destYPos = -1;
    _width = -1;
    _height = -1;
    _target = NULL;
    _visualTex = NULL;
}

Projectile::Projectile(int speed, int damage, int width, int height, int xPos, int yPos, Unit* target)
{
    _speed = speed;
    _damage = damage;
    _xPos = xPos;
    _yPos = yPos;
    _width = width;
    _height = height;
    _target = target;
    _visualTex = NULL;
}

Projectile::~Projectile()
{
    SDL_DestroyTexture(_visualTex);
}

int Projectile::update()
{
    int distanceToMove, distanceToTarget;
    int defenceTargetX, defenceTargetY;

    //Calculo da posição da torre deve levar em consideração o tamanho
    //Para que a unidade não fique em cima ou embaixo dela

    // if(_target->getXPos() > _xPos)
    // {
    //     defenceTargetX = _target->getXPos() - _target->getWidth()/2;
    // }
    // else
    // {
    //     defenceTargetX = _target->getXPos() + _target->getWidth()/2;
    // }

    // if(_target->getYPos() > _yPos)
    // {
    //     defenceTargetY = _target->getYPos() - _target->getHeight()/2;
    // }
    // else
    // {
    //     defenceTargetY = _target->getYPos() + _target->getHeight()/2;
    // }
    fprintf(stderr, "TARGET width: %d, TARGET height: %d\n", _target->getWidth(), _target->getHeight());
    fprintf(stderr, "TARGET posx: %d, TARGET posy: %d\n", _target->getXPos(),_target->getYPos());
    fprintf(stderr, "DAMAGE: %d\n", _damage);
    defenceTargetY = _target->getYPos() + _target->getWidth()/2;
    defenceTargetX = _target->getXPos() + _target->getHeight()/2;


    //Calcula a distância entre a unidade e a torre
    distanceToTarget = sqrt(pow((_xPos - defenceTargetX), 2) + pow((_yPos - defenceTargetY), 2));
    // fprintf(stderr, "DISTANCE TO TARGET: %d\n", distanceToTarget);

    //Calcula a distância que a unidade deve percorrer
    // elapsedTime = SDL_GetTicks() - _lastIterationTime;
    // distanceToMove = elapsedTime*_speed/1000;
    // _lastIterationTime = SDL_GetTicks();

    distanceToMove = 5;
    // fprintf(stderr, "DISTANCE TO MOVE: %d\n", distanceToMove);
    // fprintf(stderr, "DISTANCE TO TARGET: %d\n", distanceToTarget);

    if(distanceToMove >= distanceToTarget){
        //Caso a distância passe da torre
        distanceToMove = distanceToTarget;
    }

    //Define a ação da unidade

    if(distanceToTarget <= 0){
        //Para de andar e ataca a torre
        attack();
        // O projetil tem que ser eliminado e retirado da lista
        return 1; // Devemos Inserir an killList
    }
    else{
        //Percorre distanceToMove
        move(distanceToTarget, distanceToMove, defenceTargetX, defenceTargetY);
    }
    return 0; // Não deve ser inserido na killList
}

void Projectile::move(int distanceToTarget, int distance, int directionX, int directionY)
{
    fprintf(stderr, "DirectionX: %d, DirectionY: %d\nXPOS: %d, YPOS%d\n", directionX, directionY, _xPos, _yPos);
    //int proportion = 0;

    if(distance > 0)
    {
         //proportion = distance / distanceToTarget ; // % que temos que andar em X e Y
        _xPos = _xPos + (distance * (directionX - _xPos))/ distanceToTarget;
        _yPos = _yPos + (distance * (directionY - _yPos))/ distanceToTarget;
    }
    fprintf(stderr, "New X: %d, New Y: %d\n\n", _xPos, _yPos);
}

void Projectile::attack()
{
    printf("Atacando\n");
    _target->takeDamage(_damage);
}

void Projectile::render(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    SDL_Rect destRect;
    SDL_Surface* tempSurface;

    if(_xPos == -1 || _yPos == -1){
        fprintf(stderr, "Error, projectile has X or Y set to -1\n");
        return;
    }

    destRect.w = _width;
    destRect.h = _height;
    destRect.x = _xPos;
    destRect.y = _yPos;

    if(!renderer){
        fprintf(stderr, "Error rendering unit, renderer is NULL\n");
        return;
    }
    if(!_visualTex){
        //Define a texture da unidade
        tempSurface = IMG_Load("../img/projectile.bmp");
        if(tempSurface){
            _visualTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
        }
        else{
            fprintf(stderr, "Error loading file for projectile\n");
        }
        SDL_FreeSurface(tempSurface);
    }
    // printf("(%p)Rendering projectile to X %d, Y: %d, width: %d, height: %d\n", _visualTex, destRect.x, destRect.y, destRect.w, destRect.h);
    SDL_RenderCopy(renderer, _visualTex, NULL, &destRect);
}

Unit* Projectile::getTarget(){ return _target; }
