/*!
  \file   entity.cc
  \author Nathann Morand (70%) et Felipe Ramirez (30%)
  \date   MARS 2022
  \brief  implémentation du module "entity".
*/
#include "entity.h"
#include "squarecell.h"
#include "error_squarecell.h"
#include "constantes.h"
#include "message.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

Entity::Entity(Point position, int width, int height, char specie, int id) {
    occupiedSpace = make_shared<Squarecell> (position, width, height, specie);
    this->specie=specie;
    this->id=id;
}

void Entity::setPosition(Point newPosition) {
    (*occupiedSpace).setPosition(newPosition);
}

Point Entity::getPosition() {
    return (*occupiedSpace).getPosition();
}

void Entity::setSize(int width, int height) {
    (*occupiedSpace).setSize(height, width);
}

int Entity::getHeight() {
    return (*occupiedSpace).getHeight();
}

int Entity::getWidth() {
    return (*occupiedSpace).getWidth();
}

char Entity::getSpecie() {
    return specie;
}

int Entity::getId() {
    return id;
}

shared_ptr<Squarecell> Entity::getOccupiedSpace() {
    return occupiedSpace;
}

int Entity::findIdByOccupingPoint(Point overlappingPoint,
                                  std::vector<std::shared_ptr<Entity>> listOfEntity,
                                  char specie) {
    /*
    int x = overlappingPoint.getCoordX;
    int y = overlappingPoint.getCoordY;

    for(unsigned int i(0); i<listOfEntity.size(); i++) {
        if((*(*ListOfEntity[i]).getOccupiedSpace()).getSpecie() == specie) { //(*ListOfEntity[i]).getSpecie()
            int largeur = (*(*ListOfEntity[i]).getOccupiedSpace()).getWidth();
            int hauteur = (*(*ListOfEntity[i]).getOccupiedSpace()).getHeight();
            int pointOriginX = ((*(*ListOfEntity[i]).getOccupiedSpace()).getHitboxBotLeft()).getCoordX();
            int pointOriginY = ((*(*ListOfEntity[i]).getOccupiedSpace()).getHitboxBotLeft()).getCoordY();
            if((x+pointOriginX)<=largeur and (x+pointOriginX)=>largeur and (y+pointOriginY)<=hauteur and (y+pointOriginY)=>hauteur) {
                cout << "erreur overlaping fourmiliere" << *(*ListOfEntity[i]).getOccupiedSpace()).getWidth()

            }
        }
    }
    */
    return 0; // FAIRE TA FONCTION ICI (SAUF SI MEILLEURE IDEE)
}

/*int Entity::checkOverlap(Entity entity)
{
    // remove if not used
    return 0;
}*/