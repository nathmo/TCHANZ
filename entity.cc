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
void entity::Entity::setPosition(Point newPosition)
{
    position = newPosition;
}
squarecell::Point entity::Entity::getPosition()
{
    return position;
}
void squarecell::Entity::setsize(Point newSize)
{
    size = newSize;
}
squarecell::Point squarecell::Entity::getsize()
{
    return size;
}
char squarecell::Entity::getSpecie()
{
    return specie;
}
int squarecell::Entity::checkOverlap(Entity entity)
{
    // remove if not used
    return 0;
}
int squarecell::Entity::getId()
{
    return id;
}
void squarecell::Entity::setId(int id)
{
    this->id = id;
}
