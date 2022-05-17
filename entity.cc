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

Entity::Entity(Point position, int width, int height,
               char specie, int id, bool isPositionAtCenter) {
    occupiedSpace = make_shared<Squarecell> (position, width, height,
                                             specie, isPositionAtCenter);
    this->specie = specie;
    this->id = id;
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

void Entity::setEndOfLife(bool endOfLife) {
    this->endOfLife = endOfLife;
}

shared_ptr<Squarecell> Entity::getOccupiedSpace() {
    return occupiedSpace;
}

vector<vector<string>> Entity::exportToString() {
    cout << "trying to export a generic entity" << endl;
    exit(EXIT_FAILURE);
}

void Entity::update(vector<shared_ptr<Entity>> &entityList) {
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

shared_ptr<Entity> Entity::findByPosition(Point position,
                                          vector<shared_ptr<Entity>> listOfEntity,
                                          char specie) {
    for(auto entity:listOfEntity) {
        if((*entity).getSpecie() == specie) {
            int largeur = ((*entity).getOccupiedSpace())->getWidth();
            int hauteur = ((*entity).getOccupiedSpace())->getHeight();
            Point positionEntity = ((*entity).getOccupiedSpace())->getHitboxBotLeft();
            int match = Squarecell::countOverlap(position, 1, 1, false,
                                             positionEntity, largeur, hauteur, false);
            if(1 <= match) { //si overlap plus grand ou = a 1
                return entity; //return the entity once found
            }
        }
    }
    return nullptr; //return a value that show no entity where found
}

vector<shared_ptr<Entity>> Entity::findByID(int id,
                                            vector<shared_ptr<Entity>> listOfEntity,
                                            char specie) {
    vector<shared_ptr<Entity>> found = {};
    for(auto entity:listOfEntity) {
        if((*entity).getSpecie() == specie) {
            if((*entity).getId() == id) {
                found.push_back(entity); //return the entity once found
            }
        }
    }
    return found; //return a value that show no entity where found
}

vector<Point> Entity::findSpecie(char specie,
                                 vector<shared_ptr<Entity>> listOfEntity) {
    vector<Point> listSpecie;
    for(unsigned int i(0); i < listOfEntity.size(); i++) {
        if(((*listOfEntity[i]).getSpecie()) == specie) {
            int x=(((*listOfEntity[i]).getOccupiedSpace())
                    ->getPosition()).getCoordX();
            int y=(((*listOfEntity[i]).getOccupiedSpace())
                    ->getPosition()).getCoordY();
            listSpecie.push_back(Point(x,y));
        }
    }
    return listSpecie;
}

vector<Point> Entity::trie(Point position, vector<Point> listSpecieTrie) {
    vector<Point> newList = {};
    for(unsigned int i(0); i < .size(); i++) {
        int index = i;
        double distanceIni = Point::distanceAbs(position, listSpecieTrie[i]);
        for(unsigned int j=(i+1); j < listSpecieTrie.size(); j++) {
            if(distanceIni > Point::distanceAbs(position, listSpecieTrie[j])) {
                distanceIni = Point::distanceAbs(position, listSpecieTrie[j]);
                listSpecieTrie.erase(listSpecieTrie.begin() + j);
                listSpecieTrie.push_back(listSpecieTrie[i]); //pas perdre la 1er ligne
                index = j;
            }
        }
        newList.push_back(listSpecieTrie[index]);
    }
    return newList;
}