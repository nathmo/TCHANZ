/*!
  \file   entity.cc
  \author Nathann Morand (50%) et Felipe Ramirez (50%)
  \date   MARS 2022
  \brief  implémentation du module "entity".
*/
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"

using namespace std;

default_random_engine Entity::randGen;

Entity::Entity(Point position, int width, int height, char specie,
               int id, bool isPositionAtCenter) {
    occupiedSpace = make_shared<Squarecell> (position, width, height,
                                             specie, isPositionAtCenter);
    this->specie=specie;
    this->id=id;
    endOfLife = false;
}

void Entity::setPosition(Point newPosition) {
    (*occupiedSpace).setPosition(newPosition);
}

Point Entity::getPosition() {
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

bool Entity::getEndOfLife(){
    return endOfLife;
}

void Entity::setEndOfLife(bool endOfLife){
    this->endOfLife = endOfLife;
}

shared_ptr<Squarecell> Entity::getOccupiedSpace() {
    return occupiedSpace;
}

vector<vector<string>> Entity::exportToString() {
    cout << "trying to export a generic entity" << endl;
    exit(EXIT_FAILURE);
}

void Entity::update(vector<shared_ptr<Entity>> & entityList) {
    cout << "trying to update a generic entity" << endl;
    exit(EXIT_FAILURE);
}

void Entity::draw() {
    cout << "trying to draw a generic entity" << endl;
    exit(EXIT_FAILURE);
}

bool Entity::biasedCoinFlip(float p) {
    bernoulli_distribution bernoulli(p);
    return bernoulli(randGen);
}

int Entity::randInt(unsigned int min, unsigned int max) {
    uniform_int_distribution<unsigned> draw(min,max);
    return draw(randGen);
}

int Entity::findIdByOccupingPoint(Point overlappingPoint,
                                  vector<shared_ptr<Entity>> listOfEntity,
                                  char specie) {
    for(unsigned int i(0); i<listOfEntity.size(); i++) {
        if((*listOfEntity[i]).getSpecie() == specie) {
            int largeur = ((*listOfEntity[i]).getOccupiedSpace())->getWidth();
            int hauteur = ((*listOfEntity[i]).getOccupiedSpace())->getHeight();
            int pointOriginX = (((*listOfEntity[i]).getOccupiedSpace())
                                                    ->getHitboxBotLeft()).getCoordX();
            int pointOriginY = (((*listOfEntity[i]).getOccupiedSpace())
                                                    ->getHitboxBotLeft()).getCoordY();
            Point position2(pointOriginX,pointOriginY);
            if(Squarecell::countOverlap(overlappingPoint, 1, 1, false,
                    position2, largeur, hauteur,
                    (*listOfEntity[i]).getOccupiedSpace()->getIsPositionAtCenter())) {
                return (*listOfEntity[i]).getId(); //return id of the overlap entity
            }
        }
    }
    return errorCode; //return a value that show no entity where found
}

vector<Point> Entity::findSpecie(Point position, char specie,
                                 vector<shared_ptr<Entity>> listOfEntity) {
    vector<Point> listSpecie;

    for(unsigned int i(0); i<listOfEntity.size(); i++) {
        if(((*listOfEntity[i]).getSpecie()) == specie) {
            int x=(((*listOfEntity[i]).getOccupiedSpace())->getPosition()).getCoordX();
            int y=(((*listOfEntity[i]).getOccupiedSpace())->getPosition()).getCoordY();
            listSpecie.push_back(Point(x,y));
        }
    }
    return listSpecie;
}

vector<Point> Entity::trie(Point positionCollector, vector<Point> listSpecieTrie) {
    vector<Point> newList;

    for(unsigned int i(0); i<listSpecieTrie.size(); i++) {
        int index = i;
        double distanceIni = distance2Points(positionCollector, listSpecieTrie[i]);

        for(unsigned int j = (i+1); j<listSpecieTrie.size(); i++) {
            if(distanceIni>distance2Points(positionCollector, listSpecieTrie[j])) {
                distanceIni = distance2Points(positionCollector, listSpecieTrie[j]);
                listSpecieTrie.erase(listSpecieTrie.begin()+j);
                listSpecieTrie.push_back(listSpecieTrie[i]); //pas perdre la premiere ligne dans le cas ou distance plus petite
                index = j;
            }
        }
        newList.push_back(listSpecieTrie[index]);
    }
    return newList;
}

double Entity::distance2Points(Point positionCollector, Point point) {
    int x = positionCollector.getCoordX();
    int y = positionCollector.getCoordY();
    int x1 = point.getCoordX();
    int y1 = point.getCoordY();
    return sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
}



/*
double Entity::distance2Points(int xOrigin, int yOrigin, int xPoint, int yPoint) {
    return sqrt((xPoint-xOrigin)*(xPoint-xOrigin)+(xPoint-yOrigin)*(yPoint-yOrigin));
}


Point Entity::pointClosestCollector(int xOrigin, int yOrigin,
                                    vector<Point> listSpecieTrie) {
    int x1 = listSpecieTrie[0].getCoordX(); //faire les comparaisons aux autres de la liste
    int y1 = listSpecieTrie[0].getCoordY();
    double distance = distance2Points(xOrigin, yOrigin, x1, y1);
    for(auto point:listSpecieTrie) {
        int x2 = point.getCoordX();
        int y2 = point.getCoordY();
        if(distance<distance2Points(xOrigin, yOrigin, x1, y1)) {
            x1 = x2;
            y1 = y2;
        }
    }
    return Point(x1,y1);
}

int Entity::findPoint(Point point, vector<Point> listSpecieTrie) {
    for(int i(0); i<listSpecieTrie.size(); i++){
        if(point == listSpecieTrie[i]) {
            return i;
        }
    }
}
*/