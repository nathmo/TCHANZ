/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"
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

squarecell::Entity::Entity(Point position, Point size, char specie) {
this->position = position;
this->size = size;
this->specie = specie;
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