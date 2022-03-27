//
// Created by nathann on 27.03.22.
//

#ifndef TCHANZ_ENTITY_H
#define TCHANZ_ENTITY_H

#include "squarecell.h"

namespace entity
{
    class Entity {
    private:
        squarecell::Squarecell occupiedSpace;
        char specie;
        int id;
    public:
        Entity(squarecell::Point position, int lenght, int width, char specie, int id);

        void setPosition(squarecell::Point newPosition);

        squarecell::Point getPosition();

        void setsize(int lenght, int width);

        int getLenght();

        int getWidth();

        char getSpecie();

        int getId();
    };
}
#endif //TCHANZ_ENTITY_H