/*!
  \file   fourmi.cc
  \author Nathann Morand (30%) et Felipe Ramirez (70%)
  \date   MARS 2022
  \brief  implémentation du module "fourmi".
*/
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Fourmi::Fourmi(Point position, int age, char type, int id, int size)  :
        Entity(position, size, size, type, id, true){
    this->age = age;
    endOfLife = false;
    pathBuffer = {};
}

int Fourmi::getAge() {
    return age;
}

void Fourmi::step() {
    setPosition(pathBuffer[0]);
    pathBuffer.erase(pathBuffer.begin());
}

void Fourmi::update(vector<shared_ptr<Entity>> &entityList) {
    cout << "error, trying to update a generic fourmi object" << endl;
    exit(EXIT_FAILURE);
}

vector<vector<string>> Fourmi::exportToString() {
    vector<vector<string>> toExport;
    cout << "ERROR : exporting a generic ant type" << endl;
    exit(EXIT_FAILURE);
    return toExport;
}

void Fourmi::draw() {
    cout << "trying to draw a generic fourmi" << endl;
    exit(EXIT_FAILURE);
}

Collector::Collector(Point position, int id, int age, bool carryFood ) :
        Fourmi(position, age,fourmiCollectorCST,id,sizeC) {
    this->carryFood = carryFood;
}

void Collector::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    if(carryFood) {
        if(pathBuffer.size() > 1) { // walk toward the generator one step at a time
            step();
        } else if(pathBuffer.size() == 1) { // once reached give the food to the gener
            unloadFood(entityList);
            // ici calculer le chemin pour la prochaine bouffe et ajouter au buffer
        } else {
            // ici calculer le chemin pour la generator
        }
    } else {
        bool foodStillThere = false;
        bool foodStillClosest = true;
        if(pathBuffer.size()==0){
            foodStillThere = false;
        } else {
            foodStillThere = Squarecell::countOverlap(
                        pathBuffer[pathBuffer.size() - 1], 1, 1, nourritureCST, true);
            if(distance2Points(getPosition(),pathBuffer[pathBuffer.size()-1])>
               distance2Points(getPosition(),Collector::findClosestFood(entityList))){
                foodStillClosest = false;
            }
        }
        if(foodStillThere and foodStillClosest) {
            if(pathBuffer.size() > 1) { // walk toward the food one step at a time
                step();
            } else { // once reached mark the food for deletion
                loadFood(entityList);
                // ici calculer le chemin pour la generator
            }
        } else {
            // ici recalculer le chemin pour la prochaine bouffe et ajouter au buffer
        }
    }
}

Point Collector::findClosestFood(vector<shared_ptr<Entity>> &entityList) {
    int xOrigin = getPosition().getCoordX();
    int yOrigin = getPosition().getCoordY();
    Point positionCollector = getPosition();
    vector<Point> listSpecie = Entity::findSpecie(Point(xOrigin, yOrigin),
                                                  nourritureCST, entityList);
    vector<Point> listSpecieTrie; //liste specie meme couleur case
    //savoir si case noir ou blanche
    bool spot = false; //case noir
    if(!((xOrigin+yOrigin)%2 == 0)) {
        spot = true;
    }
    //classer les food qui sont sur meme couleur case
    for(auto entity : listSpecie) {
        int x = entity.getCoordX();
        int y = entity.getCoordY();
        if((x+y)%2 == spot) {
            listSpecieTrie.push_back(entity);
        }
    }
    vector <Point> newListTrie = Entity::trie(positionCollector, listSpecieTrie);
    return newListTrie[0];
}

void Collector::unloadFood(vector<shared_ptr<Entity>> &entityList) {
    shared_ptr<Entity> entity = Entity::findByPosition(pathBuffer[0], entityList,
                                                       fourmiGeneratorCST);
    // ensure the generator returned had the right id
    shared_ptr<Generator> gene = dynamic_pointer_cast<Generator>(entity);
    gene->addFood();
    carryFood = false;
    pathBuffer.erase(pathBuffer.begin());
}

void Collector::loadFood(vector<shared_ptr<Entity>> &entityList) {
    shared_ptr<Entity> food = Entity::findByPosition(pathBuffer[0],
                                                     entityList, nourritureCST);
    food->setEndOfLife(true);
    carryFood = true;
    pathBuffer.erase(pathBuffer.begin());
}

vector<Point> Collector::bestPathCollector(Point positionCollector, Point pointToGo) {
    double distanceInit = Entity::distance2Points(positionCollector, pointToGo);
    vector<Point> path1, path2, path3, path4;
    int index(1);
    bool first = true;
    int count(0);
    bestDiago(positionCollector, pointToGo, distanceInit, path1, count, index, first);
    index = 2;
    first = true;
    count = 0;
    bestDiago(positionCollector, pointToGo, distanceInit, path2, count, index, first);
    index = 3;
    first = true;
    count = 0;
    bestDiago(positionCollector, pointToGo, distanceInit, path3, count, index, first);
    index = 4;
    first = true;
    count = 0;
    bestDiago(positionCollector, pointToGo, distanceInit, path4, count, index, first);
    return path1; //fonction en cours de travail pour rendu 3

    return path1; //fonction en cours de travail pour rendu 3
}

void Collector::bestDiago(Point positionCollector, Point pointToGo,
                          double distanceInit, vector<Point> &pathPossibilitys,
                          int count, int &index, bool first) {
    int xOrigin = positionCollector.getCoordX();
    int yOrigin = positionCollector.getCoordY();

    if(count == 2) {
        return;
    }

    if(index == 1) { //droite haut
        path(Point(xOrigin + 1, yOrigin + 1), pointToGo, distanceInit,
             pathPossibilitys, count, index, first);
    } else if(index == 2) { //gauche haut
        path(Point(xOrigin - 1, yOrigin + 1), pointToGo, distanceInit,
             pathPossibilitys, count, index, first);
    } else if(index == 3) { //gauche bas
        path(Point(xOrigin - 1, yOrigin - 1), pointToGo, distanceInit,
             pathPossibilitys, count, index, first);
    } else { //droite bas
        path(Point(xOrigin + 1, yOrigin - 1), pointToGo, distanceInit,
             pathPossibilitys, count, index, first);
    }
}

void Collector::path(Point step, Point pointToGo, double distanceInit,
                     vector<Point> &path, int &count, int &index, bool first) {
    double newDistance = Entity::distance2Points(step, pointToGo);
    if(newDistance < 2) {
        path.push_back(step);
        return;
    }
    if(newDistance < distanceInit) {
        path.push_back(step);
        bestDiago(step, pointToGo, newDistance, path, count, index, false);
        return;
    } else {
        count++;
        if(first == true) {
            return;
        }
        if(index == 4) {
            index = 1;
            bestDiago(step, pointToGo, distanceInit, path, count, index, false);
            return;
        } else {
            index++;
            bestDiago(step, pointToGo, distanceInit, path, count, index, false);
            return;
        }
    }
}

vector<vector<string>> Collector::exportToString() {
    vector<vector<string>> vecVecStringCollector;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string carryFoodString = "False";
    if(carryFood) {
        carryFoodString = "True";
    }
    string ageString = to_string(age);
    vecVecStringCollector.push_back({x,y,ageString,carryFoodString});
    return vecVecStringCollector;
}

shared_ptr<Fourmi> Collector::importFromExtSaveCollector(vector<string> &inputBuffer,
                                                         int index) {
    if(!(inputBuffer.size()<=4)) {
        cout << "Collector : number of argument mismatch" << endl;
        throw (errorCode);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    bool conditionFood = false;
    if("true" == inputBuffer[3]) {
        conditionFood = true;
    }
    vector<Point> overlapList = Squarecell::getOverlap(Point(x, y), sizeC, sizeC,
                                                       anyCST, true);
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (errorCode);
    }
    return make_shared<Collector> (Point(x, y), index , age, conditionFood);
    }
}

void Collector::draw() {
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int id = getId()%6;

    Squarecell::diagonale(x, y, id, sizeC);
}

Defensor::Defensor(Point position, int id, int age) :
                         Fourmi(position, age,fourmiDefensorCST,id, sizeD) {
}

void Defensor::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
}

vector<vector<string>> Defensor::exportToString() {
    vector<vector<string>> vecVecStringDefensor;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string ageString = to_string(age);
    vecVecStringDefensor.push_back({x,y,ageString});
    return vecVecStringDefensor;
}

shared_ptr<Fourmi> Defensor::importFromExtSaveDefensor(vector<string> &inputBuffer,
                                                       int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Defensor : number of argument mismatch" << endl;
        throw (errorCode);
    } else {
    long int x = stoi(inputBuffer[0]);
    long int y = stoi(inputBuffer[1]);
    long int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x, y), sizeD, sizeD,
                                                       anyCST, true);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::defensor_overlap(x,y, overlapList[0].getCoordX(),
                                         overlapList[0].getCoordY());
        throw (errorCode);
    }
    return make_shared<Defensor>(Point(x, y), index,age);
    }
}

void Defensor::draw() {
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int id = getId()%6;

    Squarecell::grille(x, y, id, sizeD);
}

Predator::Predator(Point position, int id, int age) :
                       Fourmi(position, age, fourmiPredatorCST, id, sizeP) {

}

void Predator::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
}

vector<vector<string>> Predator::exportToString() {
    vector<vector<string>> vecVecStringPredator;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string ageString = to_string(age);
    vecVecStringPredator.push_back({x,y,ageString});
    return vecVecStringPredator;
}

shared_ptr<Fourmi> Predator::importFromExtSavePredator(vector<string> &inputBuffer,
                                                       int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Predator : number of argument mismatch" << endl;
        throw (errorCode);
    } else {
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        int age = stoi(inputBuffer[2]);
        vector<Point> overlapList = Squarecell::getOverlap(Point(x, y), sizeP, sizeP,
                                                           anyCST, true);
        if(overlapList.size()>0) { // ensure the ant does not collide with something
            cout<< message::predator_overlap(x, y);
            throw (errorCode);
        }
    return make_shared<Predator>(Point(x, y),index, age);
    }
}

void Predator::draw() {
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int id = getId()%6;
    Squarecell::square(x, y, id);
}

Generator::Generator(Point position, int id) :
                    Fourmi(position,0 , fourmiGeneratorCST, id, sizeG) {
    foodReceived = 0;
}

void Generator::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
}

vector<vector<string>> Generator::exportToString() {
    vector<vector<string>> vecVecStringGenerator;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string ageString = to_string(age);
    vecVecStringGenerator.push_back({x,y,ageString});
    return vecVecStringGenerator;
}

shared_ptr<Fourmi> Generator::importFromExtSaveGenerator(vector<string> &inputBuffer,
                                                         int index) {
    int x = stoi(inputBuffer[3]);
    int y = stoi(inputBuffer[4]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x, y), sizeG, sizeG,
                                                       anyCST, true);
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::generator_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (errorCode);
    }
    return make_shared<Generator>(Point(x, y), index);
}

void Generator::draw() {
    vector<vector<double>> commandList;
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = (*occupiedSpace).getHeight();
    int id = getId();
    for(int i(0); i < side; i++) {
        for(int j(0); j < side; j++) {
            Squarecell::square(x + j, y + i, id%6);
        }
    }
}

int Generator::getFood() {
    return foodReceived;
}

void Generator::addFood() {
    foodReceived++;
}

void Generator::removeFood() {
    foodReceived = 0;
}
