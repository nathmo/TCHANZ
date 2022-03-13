/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"
#include "error_squarecell.h"
#include <vector>

using namespace std;

squarecell::Point::Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
squarecell::Point::Point::Point()
{
    this->x = -1;
    this->y = -1;
}
void squarecell::Point::setPositionX(int xOrigin)
{
    x = xOrigin;
}
int squarecell::Point::getPositionX()
{
    return x;
}
void squarecell::Point::setPositionY(int yOrigin)
{
    y = yOrigin;
}
int squarecell::Point::getPositionY()
{
    return y;
}

squarecell::Entity::Entity(Point position, Point size, char specie)
{
    this->position = position;
    this->size = size;
    this->specie = specie;
}
void squarecell::Entity::setPosition(Point newPosition)
{
    position = newPosition;
}
squarecell::Point squarecell::Entity::getPosition()
{
    return position;
}
void squarecell::Entity::setsize(Point newSize)
{
    size = newSize;
}
squarecell::Point squarecell::Entity::getsize()
{
    return size;
}
char squarecell::Entity::getSpecie()
{
    return specie;
}
int squarecell::Entity::checkOverlap(Entity entity)
{
    return 0;
}

squarecell::Squarecell::Squarecell(){
    hitBoxGrid = vector<vector<bool>> (g_max, vector<bool>(g_max,false));
    entityGrid = vector<vector<char>> (g_max, vector<char>(g_max, 'E'));
}
int squarecell::Squarecell::getgMax(){
    return g_max;
}

void squarecell::Squarecell::add(Entity entity)
{
    if(squarecell::Squarecell::checkSize(entity))
    {

    }
    if(squarecell::Squarecell::checkHitbox(entity))
    {

    }
    if(squarecell::Squarecell::checkOverlap(entity))
    {

    }
}
void squarecell::Squarecell::remove(Entity entity)
{

}
bool squarecell::Squarecell::checkSize(squarecell::Entity entity)
{
    bool status = true;
    if(not((entity.getPosition().getPositionX() >= 0) and (entity.getPosition().getPositionX() < squarecell::g_max)))
    {
        error_squarecell::print_index(entity.getPosition().getPositionX(), squarecell::g_max);
        status = false;
    }
    if(not((entity.getsize().getPositionY() >= 0) and (entity.getPosition().getPositionY() < squarecell::g_max)))
    {
        error_squarecell::print_index(entity.getPosition().getPositionY(), squarecell::g_max);
        status = false;
    }
    return status;
}
bool squarecell::Squarecell::checkHitbox(Entity entity)
{
    error_squarecell::print_outside(entity.getPosition().getPositionX(),
                                     entity.getsize().getPositionX(),squarecell::g_max);
    return true;
}
int squarecell::Squarecell::checkOverlap(Entity entity)
{
    int overlappingArea = 0;
    return overlappingArea;
}