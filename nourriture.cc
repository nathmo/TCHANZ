/*!
  \file   nourriture.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "nourriture".
*/

#include "nourriture.h"
#include "squarecell.h"
#include "constantes.h"

using namespace std;

nourriture::Nourriture::Nourriture(squarecell::Point position) :
    squarecell::Entity(position, squarecell::Point(1,1), nourritureCST) {}