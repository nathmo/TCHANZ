/*!
  \file   entity.cc
  \author Nathann Morand (70%) et Felipe Ramirez (30%)
  \date   MARS 2022
  \brief  implémentation du module "entity".
*/
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "entity.h"
#include "squarecell.h"
#include "error_squarecell.h"
#include "constantes.h"
#include "message.h"

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

    for(unsigned int i(0); i<listOfEntity.size(); i++) {
        if((*listOfEntity[i]).getSpecie() == specie) { //
            int largeur = ((*listOfEntity[i]).getOccupiedSpace()).getWidth();
            int hauteur = ((*listOfEntity[i]).getOccupiedSpace()).getHeight();
            int pointOriginX = (((*listOfEntity[i]).getOccupiedSpace()).getHitboxBotLeft()).getCoordX();
            int pointOriginY = (((*listOfEntity[i]).getOccupiedSpace()).getHitboxBotLeft()).getCoordY();
            Point position2(pointOriginX,pointOriginY);

            if(not(Squarecell::countOverlap(overlappingPoint, 1, 1, position2, largeur, hauteur) == 0)) {
                cout << "overlapping" << endl;
                return 1;
            } else {
                return 0;
            }
        }
    }
}

/*int Entity::checkOverlap(Entity entity)
{
    // remove if not used
    return 0;
}*/