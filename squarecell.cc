/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"
#include "error_squarecell.h"
#include <vector>
#include <iostream>

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
    bool eligible = squarecell::Squarecell::checkSize(entity)
                and squarecell::Squarecell::checkHitbox(entity)
                and squarecell::Squarecell::checkOverlap(entity);
    if(eligible)
    {
        entityList.push_back(entity);
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
    return status; // true if all test pass, false otherwise (and display the set message)
}
bool squarecell::Squarecell::checkHitbox(Entity entity)
{
    bool status = true;
    if(((entity.getsize().getPositionX() % 2) == 0) and ((entity.getsize().getPositionY() % 2) == 0))
    {
        // check pos + size in [0;squarecell::g_max[ (even number for size)
        if(not((entity.getPosition().getPositionX()+entity.getsize().getPositionX() >= 0)
           and (entity.getPosition().getPositionX()+entity.getsize().getPositionX() < squarecell::g_max)))
        {
            error_squarecell::print_outside(entity.getPosition().getPositionX(),
                                             entity.getsize().getPositionX(), squarecell::g_max);
            status = false;
        }
        // check pos + size in [0;squarecell::g_max[ (even number for size)
        if(not((entity.getPosition().getPositionY()+entity.getsize().getPositionY() >= 0)
               and (entity.getPosition().getPositionY()+entity.getsize().getPositionY() < squarecell::g_max)))
        {
            error_squarecell::print_outside(entity.getPosition().getPositionY(),
                                             entity.getsize().getPositionY(), squarecell::g_max);
            status = false;
        }
    }
    else if (((entity.getsize().getPositionX() % 2) == 1) and ((entity.getsize().getPositionY() % 2) == 1))
    {
        // check pos + ((size-1)/2) in [0;squarecell::g_max[ (odd number for size)
        if(not((entity.getPosition().getPositionX()+entity.getsize().getPositionX() >= 0)
               and (entity.getPosition().getPositionX()+entity.getsize().getPositionX() < squarecell::g_max)))
        {
            error_squarecell::print_outside(entity.getPosition().getPositionX(),
                                             entity.getsize().getPositionX(), squarecell::g_max);
            status = false;
        }
        if(not((entity.getPosition().getPositionY()+entity.getsize().getPositionY() >= 0)
               and (entity.getPosition().getPositionY()+entity.getsize().getPositionY() < squarecell::g_max)))
        {
            error_squarecell::print_outside(entity.getPosition().getPositionY(),
                                             entity.getsize().getPositionY(), squarecell::g_max);
            status = false;
        }
    }
    else
    {
        // this should not happen since every size is supposed to be a square
        cout << "shape is not a squared" << endl;
        status = false;
        exit(0);
    }
    return status; // true if all test pass, false otherwise (and display the set message)
}
int squarecell::Squarecell::checkOverlap(Entity entity)
{
    int overlappingArea = 0;
    return overlappingArea;
}