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
}

int Fourmi::getAge() {
    return age;
}

void Fourmi::update(vector<shared_ptr<Entity>> & entityList) {
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
    if(carryFood){
        if(pathBuffer.size() > 1) { // walk toward the generator one step at a time
            setPosition(pathBuffer[0]);
            pathBuffer.erase(pathBuffer.begin());
        } else { // once reached give the food to the generator
            shared_ptr<Entity> entity = Entity::findByPosition(pathBuffer[0], entityList, fourmiGeneratorCST);
            shared_ptr<Generator> gene = dynamic_pointer_cast<Generator>(entity);
            gene->addFood();
            carryFood = false;
            pathBuffer.erase(pathBuffer.begin());
            // ici calculer le chemin pour la prochaine bouffe et ajouter au buffer
        }
    } else {
        bool foodStillThere = Squarecell::countOverlap(pathBuffer[pathBuffer.size()-1], 1, 1,
                                                  nourritureCST, true);
        bool foodStillClosest = true;
        if(distance2Points(getPosition(),pathBuffer[pathBuffer.size()-1])>
               distance2Points(getPosition(),Collector::findClosestFood(entityList))){
            foodStillClosest = false;
        }
        if(foodStillThere and foodStillClosest)
        {
            if(pathBuffer.size() > 1) { // walk toward the food one step at a time
                setPosition(pathBuffer[0]);
                pathBuffer.erase(pathBuffer.begin());
            } else { // once reached mark the food for deletion
                shared_ptr<Entity> food = Entity::findByPosition(pathBuffer[0], entityList, nourritureCST);
                food->setEndOfLife(true);
                carryFood = true;
                pathBuffer.erase(pathBuffer.begin());
                // ici calculer le chemin pour la generator
            }
        } else {
            // ici recalculer le chemin pour la prochaine bouffe et ajouter au buffer
        }
    }
}

Point Collector::findClosestFood(vector<shared_ptr<Entity>> &entityList){
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

vector<Point> Collector::bestPathCollector(Point positionCollector,
                                           Point newListTrie) {
    double distanceInit = Entity::distance2Points(positionCollector, newListTrie);
    vector<Point> path1, path2, path3, path4;
    int index(1);
    bool first = true; //savoir si premier mouvement si ca s eloigne break direct
    bool stop = false; //sortir fonction bestDiago si vrai
    cout << "begin path1" << endl;
    cout << "-----------------------------------------------------" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path1,
              index, first, stop);
    ++index;
    stop = false;
    cout << "-----------------------------------------------------" << endl;
    cout << "begin path2" << endl;
    cout << "-----------------------------------------------------" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path2,
              index, first, stop);
    ++index;
    stop = false;
    cout << "-----------------------------------------------------" << endl;
    cout << "begin path3" << endl;
    cout << "-----------------------------------------------------" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path3,
              index, first, stop);
    ++index;
    stop = false;
    cout << "-----------------------------------------------------" << endl;
    cout << "begin path4" << endl;
    cout << "-----------------------------------------------------" << endl;
    bestDiago(positionCollector, newListTrie, distanceInit, path4,
              index, first, stop);

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
        cout << "choix path1" << endl;
        return path1;
    } else if(bestPath == 2) {
        cout << "choix path2" << endl;
        return path2;
    } else if(bestPath == 3) {
        cout << "choix path3" << endl;
        return path3;
    } else {
        cout << "choix path4" << endl;
        return path4;
    }
}

void Collector::bestDiago(Point positionCollector, Point newListTrie,
                          double distanceInit, vector<Point> &path,
                          int index, bool first, bool &stop) {
    int xOrigin = positionCollector.getCoordX();
    int yOrigin = positionCollector.getCoordY();

    if(distanceInit == 0) {
        cout << "premier boucle if distanceInit: " << distanceInit << " index: " << index << endl;
        cout << "xOrigin: " << xOrigin << "yOrigin: " << yOrigin << endl;
        return;
    } else {
        //cout << "je rentre en force dans le else" << endl; // ca rentre pas si le if est vrai mais alors pourquoi??????
        if(index == 1) { // droite haut
            Point step = Point(xOrigin + 1, yOrigin + 1);
            cout << "-----> diago droite haut" << endl;
            cout << "x: " << step.getCoordX() << " y: " << step.getCoordY() << endl;
            if(distanceInit > Entity::distance2Points(step, newListTrie)) {
                path.push_back(step);
                bestDiago(step, newListTrie,
                          Entity::distance2Points(step, newListTrie), path, 1, false,
                          stop);
                return;
            } else if(distanceInit <= Entity::distance2Points(step, newListTrie)) {
                cout << "distanceInit: " << distanceInit << " distance2: "
                     << distance2Points(step, newListTrie) << endl;
                if(first) {
                    stop = true;
                    return;
                }
                index++;
                cout << "changement d index a 2 avec x: " << xOrigin << " y: "
                     << yOrigin << endl;

                bestDiago(Point(xOrigin, yOrigin), newListTrie, distanceInit,
                          path, index, false, stop);
                return;
            }
        }
        if(index == 2) { // gauche haut
            Point step = Point(xOrigin - 1, yOrigin + 1);
            cout << "-----> diago gauche haut" << endl;
            cout << "x: " << step.getCoordX() << " y: " << step.getCoordY() << endl;
            if(distanceInit > Entity::distance2Points(step, newListTrie)) {
                path.push_back(step);
                bestDiago(step, newListTrie,
                          Entity::distance2Points(step, newListTrie),
                          path, 2, false, stop);
                return;
            } else if(distanceInit <= Entity::distance2Points(step, newListTrie)) {
                cout << "distanceInit: " << distanceInit << " distance2: "
                     << distance2Points(step, newListTrie) << endl;
                if(first) {
                    stop = true;
                    return;
                }
                index++;
                cout << "changement d index a 3 avec x: " << xOrigin << " y: "
                     << yOrigin << endl;
                bestDiago(Point(xOrigin, yOrigin), newListTrie, distanceInit,
                          path, index, false, stop);
                return;
            }
        }
        if(index == 3) { // gauche bas
            Point step = Point(xOrigin - 1, yOrigin - 1);
            cout << "-----> diago gauche bas" << endl;
            cout << "x: " << step.getCoordX() << " y: " << step.getCoordY() << endl;
            if(distanceInit > Entity::distance2Points(step, newListTrie)) {
                path.push_back(step);
                bestDiago(step, newListTrie,
                          Entity::distance2Points(step, newListTrie),
                          path, 3, false, stop);
                return;
            } else if(distanceInit <= Entity::distance2Points(step, newListTrie)) {
                cout << "distanceInit: " << distanceInit << " distance2: "
                     << distance2Points(step, newListTrie) << endl;
                if(first) {
                    stop = true;
                    return;
                }
                index++;
                cout << "changement d index a 4 avec x: " << xOrigin << " y: "
                     << yOrigin << endl;
                bestDiago(Point(xOrigin, yOrigin), newListTrie, distanceInit,
                          path, index, false, stop);
                return;
            }
        }
        if(index == 4) { // droite bas
            Point step = Point(xOrigin + 1, yOrigin - 1);
            cout << "-----> diago droite bas" << endl;
            cout << "x: " << step.getCoordX() << " y: " << step.getCoordY() << endl;
            if(distanceInit > Entity::distance2Points(step, newListTrie)) {
                cout << " boucle if : distanceInit: " << distanceInit
                     << " distance2: " << distance2Points(step, newListTrie) << endl;
                if(Entity::distance2Points(step, newListTrie) == 0) {
                    cout << "je suis dedans tkt bg" << endl;
                    bestDiago(step, newListTrie,
                              Entity::distance2Points(step, newListTrie),
                              path, 4, false, stop);
                    return;
                    //return;
                } else {
                    cout << "je suis dans index 4 le if distanceInit > distance2"
                         << endl;
                    path.push_back(step);
                    bestDiago(step, newListTrie,
                              Entity::distance2Points(step, newListTrie),
                              path, 4, false, stop);
                    return;
                }
            } else if(distanceInit <= Entity::distance2Points(step, newListTrie)) {
                cout << "distanceInit: " << distanceInit << " distance2: "
                     << distance2Points(step, newListTrie) << endl;
                if(first) {
                    stop = true;
                    return;
                }
                index = 1;
                bestDiago(Point(xOrigin, yOrigin), newListTrie, distanceInit,
                          path, index, false, stop);
                return;

                /*
                bestDiago(step, newListTrie,
                          Entity::distance2Points(step, newListTrie),
                          path, index, false, stop);
                */
            }
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
    return make_shared<Collector> (Point(x,y), index , age, conditionFood);
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
}

Defensor::Defensor(Point position, int id, int age) :
                        Fourmi(position, age,fourmiDefensorCST,id, sizeD)  {
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
    int colorCode = lightColor; //on commence en bas a gauche

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
    Squarecell::square(x + 1, y + 1, id);;//change color center to dark
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

void Generator::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    if(foodReserve<=0) {
        endOfLife = true; // no food -> no generator -> no update, they all DIE !
    }
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

double Generator::getFood(){
    return foodReserve;
}

void Generator::setFood(double food){
    foodReserve = food;
}

void Generator::addFood(){
    foodReserve = foodReserve + val_food;
}

void Generator::removeFood(double consumption){
    foodReserve = foodReserve - consumption;
}
