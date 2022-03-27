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

entity::Entity::Entity(squarecell::Point position, int lenght, int width, char specie, int id)
{
    occupiedSpace = squarecell::Squarecell(position, lenght, width);
    this->specie=specie;
    this->id=id;
}
void entity::Entity::setPosition(squarecell::Point newPosition)
{
    occupiedSpace.setPosition(newPosition);
}
squarecell::Point entity::Entity::getPosition()
{
    return occupiedSpace.getPosition();
}
void entity::Entity::setsize(int lenght, int width)
{
    occupiedSpace.setSize(lenght, width);
}
int entity::Entity::getHeight()
{
    return occupiedSpace.getHeight();
}
int entity::Entity::getWidth()
{
    return occupiedSpace.getWidth();
}
char entity::Entity::getSpecie()
{
    return specie;
}
int entity::Entity::getId()
{
    return id;
}
/*int entity::Entity::checkOverlap(Entity entity)
{
    // remove if not used
    return 0;
}*/