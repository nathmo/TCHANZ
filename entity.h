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
#include <random>
#include "squarecell.h"

class Entity {
protected:
    std::shared_ptr<Squarecell> occupiedSpace;
    char specie;
    unsigned long id;
    bool endOfLife;
    static std::default_random_engine randGen;

public:
    Entity(Point position, int width, int height, char specie,
           int id, bool isPositionAtCenter);
    void setPosition(Point newPosition);
    Point getPosition();
    void setSize(int width, int height);
    int getHeight();
    int getWidth();
    char getSpecie();
    int getId();
    bool getEndOfLife();
    void setEndOfLife(bool endOfLife);
    std::shared_ptr<Squarecell> getOccupiedSpace();
    virtual std::vector<std::vector<std::string>> exportToString();
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual void draw();
    bool static biasedCoinFlip(float p);
    int static randInt(unsigned int min, unsigned int max);
    // return the id of a selected specie lying on a point if it exist
    static int findIdByOccupingPoint(Point overlappingPoint,
                                    std::vector<std::shared_ptr<Entity>> listOfEntity,
                                    char specie);
    std::vector<Point> findSpecie(Point position, char specie,
                                  std::vector<std::shared_ptr<Entity>> listOfEntity);
    std::vector<Point> trie(Point positionCollector,
                            std::vector<Point> listSpecieTrie);
    double distance2Points(Point positionCollector, Point point);
    //Point pointClosestCollector(Point positionCollector,
    //                            std::vector<Point> listSpecieTrie);
    //int findPoint(Point point, std::vector<Point> listSpecieTrie);
};

#endif //TCHANZ_ENTITY_H