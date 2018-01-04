#include <SDL2/SDL_image.h>
#include "Projectile.h"

PROJECTILE createProjectile(UNIT* target, int xPos, int yPos, int attackDamage)
{
    PROJECTILE proj;

    proj._speed = 2;
    proj._damage = attackDamage;
    proj._xPos = xPos;
    proj._yPos = yPos;
    proj._destXPos = target->_xPos;
    proj._destYPos = target->_yPos;
    proj._width = 4;
    proj._height = 4;
    proj._visualTex = NULL;
    proj._target = target;
    proj._isDead = false;

    return proj;
}

/* Desaloca os dados referentes a um projétil */
void deleteProjectile(PROJECTILE* proj)
{
    SDL_DestroyTexture(proj->_visualTex);
}

void projectileUpdate(PROJECTILE* proj)
{
    int distanceToMove, distanceToTarget;
    int defenceTargetX, defenceTargetY;

    if(proj->_isDead)
    {
        return;
    }

    defenceTargetY = proj->_target->_yPos + proj->_target->_width/2;
    defenceTargetX = proj->_target->_xPos + proj->_target->_height/2;

    //Calcula a distância entre a unidade e a torre
    distanceToTarget = sqrt(pow((proj->_xPos - defenceTargetX), 2) + pow((proj->_yPos - defenceTargetY), 2));
    distanceToMove = 5;
    //TODO: fazer o cálculo similar ao das unidades

    if(distanceToMove >= distanceToTarget){
        //Caso a distância passe da torre
        distanceToMove = distanceToTarget;
    }

    //Define a ação da unidade
    if(proj->_xPos >= proj->_target->_xPos && proj->_xPos <= proj->_target->_xPos + proj->_target->_width){
        if(proj->_yPos >= proj->_target->_yPos && proj->_yPos <= proj->_target->_yPos + proj->_target->_height){
            //Projétil está dentro da área do seu alvo
            projectileAttack(proj, proj->_target);
            return;
        }
    }
    else{
        //Percorre distanceToMove
        projectileMove(proj, distanceToTarget, distanceToMove, defenceTargetX, defenceTargetY);
    }
}

void projectileMove(PROJECTILE* proj, int distanceToTarget, int distance, int directionX, int directionY)
{
    if(distance > 0)
    {
        proj->_xPos = proj->_xPos + (distance * (directionX - proj->_xPos))/ distanceToTarget;
        proj->_yPos = proj->_yPos + (distance * (directionY - proj->_yPos))/ distanceToTarget;
    }
}

void projectileAttack(PROJECTILE* proj, UNIT* target)
{
    takeDamage(target, proj->_damage);
    proj->_isDead = true;
}

bool projectileRender(PROJECTILE* proj, SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    SDL_Rect destRect;
    SDL_Surface* tempSurface;

    if(proj->_xPos == -1 || proj->_yPos == -1){
        fprintf(stderr, "Error, projectile has X or Y set to -1\n");
        return false;
    }

    destRect.w = proj->_width;
    destRect.h = proj->_height;
    destRect.x = proj->_xPos;
    destRect.y = proj->_yPos;

    if(!renderer){
        fprintf(stderr, "Error rendering unit, renderer is NULL\n");
        return false;
    }
    if(!proj->_visualTex){
        //Define a texture da unidade
        tempSurface = IMG_Load(PROJECTILE_BMP_FILE);
        if(tempSurface){
            proj->_visualTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
        }
        else{
            fprintf(stderr, "Error loading file for projectile\n");
        }
        SDL_FreeSurface(tempSurface);
    }

    if(SDL_RenderCopy(renderer, proj->_visualTex, NULL, &destRect) < 0){
        // Caso de erro, pode ser causado por uma textura perdida, força a recriação
        SDL_DestroyTexture(proj->_visualTex);
        proj->_visualTex = NULL;
        return false;
    }

    return true;
}
