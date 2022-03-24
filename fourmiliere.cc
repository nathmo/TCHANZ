/*!
  \file   fourmiliere.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "fourmiliere".
*/


#include "fourmiliere.h"
#include "squarecell.h"
#include "constantes.h"
using namespace std;

fourmiliere::Fourmiliere::Fourmiliere(squarecell::Point position, squarecell::Point size, int total_food, int nbC, int nbD, int nbP ) :
        squarecell::Entity(position, size, fourmilliereCST)
{
    foodReserve = total_food;
    this->nbC=nbC;
    this->nbD=nbD;
    this->nbP=nbP;
}
void fourmiliere::Fourmiliere::update()
{

}