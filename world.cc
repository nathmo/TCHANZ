/*!
  \file   world.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   AVRIL 2022
  \brief  implémentation du module "world".
*/

#include <string>
#include <memory>
#include <vector>
#include "entity.h"
#include "nourriture.h"
#include "fourmiliere.h"
#include "world.h"

using namespace std;

void World::addNourriture(shared_ptr<Nourriture> nourriture){
    nourritureList.push_back(nourriture);
}
void World::addFourmilliere(shared_ptr<Fourmiliere> fourmilliere){
    nourritureList.push_back(fourmilliere);
}

void World::delEntity(shared_ptr<Entity> entity){

}