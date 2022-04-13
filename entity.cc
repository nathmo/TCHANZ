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

Entity::Entity(Point position, int width, int height, char specie, int id) {
    occupiedSpace = make_shared<Squarecell> (position, width, height, specie);
    this->specie=specie;
    this->id=id;
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

shared_ptr<Squarecell> Entity::getOccupiedSpace() {
    return occupiedSpace;
}

void Entity::update(){
    cout << "trying to update a generic entity" << endl;
    exit(EXIT_FAILURE);
}

vector<vector<double>> Entity::draw(){
    cout << "trying to draw a generic entity" << endl;
    exit(EXIT_FAILURE);
}

vector<vector<string>> Entity::exportToString(){
    cout << "trying to export a generic entity" << endl;
    exit(EXIT_FAILURE);
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
            if(Squarecell::countOverlap(overlappingPoint, 1, 1,
                                        position2, largeur, hauteur)) {
                return (*listOfEntity[i]).getId(); //return id of the overlap entity
            }
        }
    }
    return errorCode; //return a value that show no entity where found
}
/*
vector<Point> Entity::findSpecie(Point position, char specie, listOfEntity) {
    vector<Point> listSpecie;

    for(int i(0); i<listOfEntity.size(); i++) {
        if(((*listOfEntity[i]).getSpecie()) == specie) {
            int x=(((*listOfEntity[i]).getOccupiedSpace())->getPosition()).getCoordX();
            int y=(((*listOfEntity[i]).getOccupiedSpace())->getPosition()).getCoordY();
            listSpecie.push_back(Point(x,y));
        }
    }

    sort(listSpecie.begin(), listSpecie.end(), Entity::distance2Points());

    double distanceInitial = distance2Points(position, listSpecie[0]);

    for(unsigned int i(1); i<listSpecie.size(); i++) {
        if(distanceInitial > distance2Points(position, listSpecie[i])) {
            //faut switch les deux dans le tableau

            distanceInitial = distance2Points(position, listSpecie[i]);
        }
    }
    return listSpecie;
}

double Entity::distance2Points(Point position, Point positionSpecie) {
    int x = position.getCoordX();
    int y = position.getCoordY();
    int x2 = positionSpecie.getCoordX();
    int y2 = positionSpecie.getCoordY();
    double distance = sqrt((x2-x)*(x2-x) + (y2-y)*(y2-y));

    return distance;
}

bool Entity::isThere() {

    return true;
}
*/