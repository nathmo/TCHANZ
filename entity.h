//
// Created by nathann on 27.03.22.
//

#ifndef TCHANZ_ENTITY_H
#define TCHANZ_ENTITY_H

#include "squarecell.h"


class Entity {
protected:
    std::shared_ptr<Squarecell> occupiedSpace;
    char specie;
    unsigned long id;

public:
    Entity(Point position, int width, int height, char specie, int id);
    void setPosition(Point newPosition);
    Point getPosition();
    void setSize(int width, int height);
    int getHeight();
    int getWidth();
    char getSpecie();
    int getId();
    std::shared_ptr<Squarecell> getOccupiedSpace();
    //virtual void update();
    //virtual void check();
    static int findIdByOccupingPoint(Point overlappingPoint,
                                     std::vector<std::shared_ptr<Entity>> listOfEntity,
                                     char specie);
};

#endif //TCHANZ_ENTITY_H