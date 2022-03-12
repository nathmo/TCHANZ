/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"

using namespace std;

Squarecell::Squarecell(int gmax){
    gMax = gmax;
    hitBoxGrid = vector<vector<bool>> (g_max, vector<bool>(g_max,false));
    entityGrid = vector<vector<char>> (g_max, vector<char>(g_max, 'E'));
}
int Squarecell::getgMax(){
    return gMax;
}

void Squarecell::add(Entity entity)
{

}
void Squarecell::remove(Entity entity)
{

}
bool Squarecell::checkSize(Entity entity)
{

}
bool Squarecell::checkHitbox(Entity entity)
{

}
bool Squarecell::checkHitbox(Entity entity)
{

}
int Squarecell::checkOverlap(Entity entity)
{

}