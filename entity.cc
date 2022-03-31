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

entity::Entity::Entity(squarecell::Point position, int width, int height, char specie, int id) { //minuscule a la fonction
    occupiedSpace = make_shared<squarecell::Squarecell>(position, width, height, specie);
    this->specie=specie;
    this->id=id;
}

void entity::Entity::setPosition(squarecell::Point newPosition) {
    (*occupiedSpace).setPosition(newPosition);
}

squarecell::Point entity::Entity::getPosition() {
    return (*occupiedSpace).getPosition();
}

void entity::Entity::setSize(int width, int height) {
    (*occupiedSpace).setSize(height, width);
}

int entity::Entity::getHeight() {
    return (*occupiedSpace).getHeight();
}

int entity::Entity::getWidth() {
    return (*occupiedSpace).getWidth();
}

char entity::Entity::getSpecie() {
    return specie;
}

int entity::Entity::getId() {
    return id;
}

shared_ptr<squarecell::Squarecell> entity::Entity::getOccupiedSpace() {
    return occupiedSpace;
}

int entity::Entity::findIdByOccupingPoint(squarecell::Point overlappingPoint,
                                          std::vector<std::shared_ptr<entity::Entity>> ListOfEntity) {
    return 0; // FAIRE TA FONCTION ICI (SAUF SI MEILLEURE IDEE)
}

/*int entity::Entity::checkOverlap(Entity entity)
{
    // remove if not used
    return 0;
}*/