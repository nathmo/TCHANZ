//
// Created by nathann on 27.03.22.
//

#ifndef TCHANZ_ENTITY_H
#define TCHANZ_ENTITY_H

#include "squarecell.h"

namespace entity
{
    class Entity {
    protected:
        std::shared_ptr<squarecell::Squarecell> occupiedSpace;
        char specie;
        unsigned long id;
    public:
        Entity(squarecell::Point position, int height, int width, char specie, int id,bool isAnthill);
        void setPosition(squarecell::Point newPosition);

        squarecell::Point getPosition();

        void setSize(int height, int width);

        int getHeight();

        int getWidth();

        char getSpecie();

        int getId();
    };
}
#endif //TCHANZ_ENTITY_H