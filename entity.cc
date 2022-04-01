//
// Created by nathann on 27.03.22.
//

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

Entity::Entity(squarecell::Point position, int width, int height, char specie, int id) {
    occupiedSpace = make_shared<squarecell::Squarecell>(position, width, height, specie);
    this->specie=specie;
    this->id=id;
}

void Entity::setPosition(squarecell::Point newPosition) {
    (*occupiedSpace).setPosition(newPosition);
}

squarecell::Point Entity::getPosition() {
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

shared_ptr<squarecell::Squarecell> Entity::getOccupiedSpace() {
    return occupiedSpace;
}

int Entity::findIdByOccupingPoint(squarecell::Point overlappingPoint,
                                          std::vector<std::shared_ptr<Entity>> ListOfEntity, char specie) {
    /*
    int x = overlappingPoint.getCoordX;
    int y = squarecell::overlappingPoint.getCoordY;

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