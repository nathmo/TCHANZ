/*!
  \file   entity.h
  \author Nathann Morand (70%) et Felipe Ramirez (30%)
  \date   MARS 2022
  \brief  prototype du module "entity".
*/
#ifndef TCHANZ_ENTITY_H
#define TCHANZ_ENTITY_H

#include <string>
#include <vector>
#include <memory>
#include "squarecell.h"

class Entity {
protected:
    std::shared_ptr<Squarecell> occupiedSpace;
    char specie;
    unsigned long id;
    bool endOfLife;
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
    virtual std::vector<std::vector<std::string>> exportToString();
    virtual void update(std::vector<std::shared_ptr<Entity>> & entityList);
    virtual void draw();
    // return the id of a selected specie lying on a point if it exist
    static int findIdByOccupingPoint(Point overlappingPoint,
                                     std::vector<std::shared_ptr<Entity>> listOfEntity,
                                     char specie);
    std::vector<Point> findSpecie(Point position, char specie, std::vector<std::shared_ptr<Entity>> listOfEntity);
    Point pointClosestCollector(int xOrigin, int yOrigin,
                                        std::vector<Point> listSpecieTrie);
    double distance2Points(int xOrigin, int yOrigin, int x1, int y1);
    // bool isThere();
};

#endif //TCHANZ_ENTITY_H