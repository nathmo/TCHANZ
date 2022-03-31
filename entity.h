//
// Created by nathann on 27.03.22.
//

#ifndef TCHANZ_ENTITY_H
#define TCHANZ_ENTITY_H

#include "squarecell.h"

namespace entity {
    class Entity {
    protected:
        std::shared_ptr<squarecell::Squarecell> occupiedSpace;
        char specie;
        unsigned long id;

    public:
        Entity(squarecell::Point position, int width, int height, char specie, int id);
        void setPosition(squarecell::Point newPosition);
        squarecell::Point getPosition();
        void setSize(int width, int height);
        int getHeight();
        int getWidth();
        char getSpecie();
        int getId();
        std::shared_ptr<squarecell::Squarecell> getOccupiedSpace();
        static int findIdByOccupingPoint(squarecell::Point overlappingPoint,
                                         std::vector<std::shared_ptr<entity::Entity>> ListOfEntity);
    };
}
#endif //TCHANZ_ENTITY_H