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
#include <gtkmm/drawingarea.h>
#include <gtkmm/frame.h>
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

void Entity::draw(const Cairo::RefPtr<Cairo::Context>& cr){
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

vector<Point> Entity::findSpecie(char specie) {
    vector<Point> listSpecie;

    for(int i(0); i<listOfEntity.size(); i++){
        if(((*listOfEntity[i]).getSpecie()) == specie) {
            int x=(((*listOfEntity[i]).getOccupiedSpace())->getPosition()).getCoordX();
            int y=(((*listOfEntity[i]).getOccupiedSpace())->getPosition()).getCoordY();
            listSpecie.push_back(Point(x,y));
        }
    }
    return listSpecie;
}

bool isThere() {
    return true;
}