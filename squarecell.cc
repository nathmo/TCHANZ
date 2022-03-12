/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"
#include <vector>

using namespace std;

squarecell::Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
squarecell::Point::Point()
{
    this->x = -1;
    this->y = -1;
}

squarecell::Entity::Entity(Point position, Point size, char specie) {
this->position = position;
this->size = size;
this->specie = specie;
}

squarecell::Squarecell::Squarecell(int gmax){
    gMax = gmax;
    hitBoxGrid = vector<vector<bool>> (gmax, vector<bool>(gmax,false));
    entityGrid = vector<vector<char>> (gmax, vector<char>(gmax, 'E'));
}
int squarecell::Squarecell::getgMax(){
    return gMax;
}

void squarecell::Squarecell::add(Entity entity)
{

}
void squarecell::Squarecell::remove(Entity entity)
{

}
bool squarecell::Squarecell::checkSize(Entity entity)
{
    return true;
}
bool squarecell::Squarecell::checkHitbox(Entity entity)
{
    return true;
}
int squarecell::Squarecell::checkOverlap(Entity entity)
{
    int overlappingArea = 0;
    return overlappingArea;
}