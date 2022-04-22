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
        Entity(position, size, size, type, id, true) {
    this->age = age;
    endOfLife = false;
}

int Fourmi::getAge(){
    return age;
}

void Fourmi::update(vector<shared_ptr<Entity>> & entityList) {
    cout << "error, trying to update a generic fourmi object" << endl;
    exit(EXIT_FAILURE);
}

vector<vector<string>> Fourmi::exportToString(){
    vector<vector<string>> toExport;
    cout << "ERROR : exporting a generic ant type" << endl;
    exit(EXIT_FAILURE);
    return toExport;
}

void Fourmi::draw(){
    cout << "trying to draw a generic fourmi" << endl;
    exit(EXIT_FAILURE);
}

Collector::Collector(Point position, int id, int age, bool carryFood ) :
        Fourmi(position, age,fourmiCollectorCST,id,sizeC) {
    this->carryFood = carryFood;
}

void Collector::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    cout << "ici0"  << endl;
    int xOrigin = getPosition().getCoordX();
    int yOrigin = getPosition().getCoordY();
    Point positionCollector = getPosition();
    vector<Point> listSpecie = Entity::findSpecie(Point(xOrigin, yOrigin), nourritureCST, entityList);
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
    vector<Point> newListTrie = Entity::trie(positionCollector, listSpecieTrie);
    cout << "ici1"  << endl;
    pathBuffer = bestPathCollector(positionCollector, newListTrie[0]);
    cout << "sortie bestPathCollector" << endl;
    for(auto element:pathBuffer){
        cout << "x " << element.getCoordX() << endl;
        cout << "y " << element.getCoordY() << endl;
    }
    if(pathBuffer.size() != 0) {
        setPosition(pathBuffer[0]); // le segmentation fault ici surement rien dedans probleme fonction d avant
        pathBuffer.erase(pathBuffer.begin());
    }
}

vector<Point> Collector::bestPathCollector(Point positionCollector, Point newListTrie){
    double distanceInit = Entity::distance2Points(positionCollector, newListTrie);
    vector<Point> path1, path2, path3, path4;
    int index(1);
    bool first; // savoir si premier mouvement si ca s eloigne break direct dans best diago
    bool stop = false; //sortir fonction bestDiago si vrai
    cout << "begin path1" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path1, index, first, stop); // on commence celui en haut gauche premier mouvement
    ++index;
    stop = false;
    cout << "begin path2" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path2, index, first, stop);
    ++index;
    stop = false;
    cout << "begin path3" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path3, index, first, stop);
    ++index;
    stop = false;
    cout << "begin path4" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path4, index, first, stop);
    cout << "fini tous paths" << endl;
    unsigned int bestPath(0);
    if(!(path1.size()==0)) {
        bestPath = 1;
    }
    if(bestPath > path2.size() && (path2.size() != 0)) {
        bestPath = 2;
    }
    if(bestPath > path3.size() && (path3.size() != 0)) {
        bestPath = 3;
    }
    if(bestPath > path4.size() && (path4.size() != 0)) {
        bestPath = 4;
    }

    if(bestPath == 1) {
        return path1;
    } else if(bestPath == 2) {
        return path2;
    } else if(bestPath == 3) {
        return path3;
    } else {
        return path4;
    }
}

void Collector::bestDiago(Point positionCollector, Point newListTrie, double distanceInit, vector<Point> &path, int index, bool first, bool &stop) {
    int xOrigin = positionCollector.getCoordX();
    int yOrigin = positionCollector.getCoordY();
    bool condition = true;

    if(distanceInit == 0) {
        return;
    }
    if(index == 1) { // droite haut
        Point step = Point(xOrigin + 1, yOrigin + 1);
        if(distanceInit > Entity::distance2Points(step, newListTrie)) {
            path.push_back(step);
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie), path, 1, false, stop);
        } else if(distanceInit < Entity::distance2Points(step, newListTrie)) {
            if(first) {
                stop = true;
                return;
            }
            index++;
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie), path, index, false, stop);
        }
    }
    if(index == 2) { // gauche haut
        Point step = Point(xOrigin - 1, yOrigin + 1);
        if(distanceInit > Entity::distance2Points(step, newListTrie)) {
            path.push_back(step);
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie),
                      path, 2, false, stop);
        } else if(distanceInit < Entity::distance2Points(step, newListTrie)) {
            if(first) {
                stop = true;
                return;
            }
            index++;
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie),
                      path, index, false, stop);
        }
    }
    if(index == 3) { // gauche bas
        Point step = Point(xOrigin - 1, yOrigin - 1);
        if (distanceInit > Entity::distance2Points(step, newListTrie)) {
            path.push_back(step);
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie),
                      path, 3, false, stop);
        } else if(distanceInit < Entity::distance2Points(step, newListTrie)) {
            if (first) {
                stop = true;
                return;
            }
            index++;
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie),
                      path, index, false, stop);
        }
    }
    if(index == 4) { // droite bas
        Point step = Point(xOrigin + 1, yOrigin - 1);
        if(distanceInit > Entity::distance2Points(step, newListTrie)) {
            path.push_back(step);
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie),
                      path, 4, false, stop);
        } else if(distanceInit < Entity::distance2Points(step, newListTrie)) {
            if(first) {
                stop = true;
                return;
            }
            index++;
            bestDiago(step, newListTrie,
                      Entity::distance2Points(step, newListTrie),
                      path, index, false, stop);
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
        throw (-1);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    bool conditionFood = false;
    if("true" == inputBuffer[3]) {
        conditionFood = true;
    }
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeC, sizeC,
                                                       anyCST, true);
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Collector>(Point(x,y), index , age, conditionFood);
    }
}

void Collector::draw() {
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = 3;
    int id = getId()%6;
    int lightColor = id+6;
    int colorCode = id; //on commence en bas a gauche donc foncé au debut
   // int xBotLeft, int yBotLeft,  int sizeSide, int colorCode
    for (int i(0); i < side; i++) {
        for (int j(0); j < side; j++) {
            Squarecell::square(x + j, y + i, colorCode);
            if (colorCode == id) {
                colorCode = lightColor;
            } else {
                colorCode = id;
            }
        }
    }
}

Defensor::Defensor(Point position, int id, int age) :
        Fourmi(position, age,fourmiDefensorCST,id, sizeD)  {
}

void Defensor::update(vector<shared_ptr<Entity>> & entityList) {
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
        throw (-1);
    } else {
    long int x = stoi(inputBuffer[0]);
    long int y = stoi(inputBuffer[1]);
    long int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeD, sizeD,
                                                       anyCST, true);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::defensor_overlap(x,y, overlapList[0].getCoordX(),
                                         overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Defensor>(Point(x,y), index,age);
    }
}

void Defensor::draw() {
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = 3;
    int id = getId()%6;
    int lightColor = id+6;
    int colorCode = lightColor; //on commence en bas a gauche donc clair au debut

    // int xBotLeft, int yBotLeft,  int sizeSide, int colorCode

    for(int i(0); i < side; i++) {
        for(int j(0); j < side; j++) {
            Squarecell::square(x + j, y + i, colorCode);
            if(colorCode == id) {
                colorCode = lightColor;
            } else {
                colorCode = id;
            }
        }
    }
    Squarecell::square(x + 1, y + 1, id);; // change color of center back to dark
}

Predator::Predator(Point position, int id, int age) :
                       Fourmi(position, age, fourmiPredatorCST, id, sizeP) {
}

void Predator::update(vector<shared_ptr<Entity>> & entityList) {
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
        throw (-1);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeP, sizeP,
                                                       anyCST, true);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::predator_overlap(x,y);
        throw (-1);
    }
    return make_shared<Predator>(Point(x,y),index,age);
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
}

void Generator::update(vector<shared_ptr<Entity>> & entityList) {
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
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeG, sizeG,
                                                       anyCST, true);
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::generator_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Generator>(Point(x,y), index);
}

void Generator::draw() {
    vector <vector<double>> commandList;
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
