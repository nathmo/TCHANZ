/*!
  \file   fourmi.cc
  \author Nathann Morand (50%) et Felipe Ramirez (50%)
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

void Fourmi::step(vector<shared_ptr<Entity>> &entityList) {
    if(entityList.size()>0) {
        int height = getHeight();
        int width = getWidth();
        int nextStepOverlap=0; // ensure the path is free
        setSize(0,0); // ensure the next step is free
        // (but need to remove itself to prevent self collision) (food are ignored)
        nextStepOverlap = Squarecell::countOverlap(pathBuffer[0], width, height,
                                           (anyCST ^ (nourritureCST)), true);
        setSize(width, height); // back to normal size
        if(nextStepOverlap == 0) {
            setPosition(pathBuffer[0]);
            pathBuffer.erase(pathBuffer.begin());
            cout <<"step" << endl;
        } else {
            cout <<"ronflex on path" << endl;
        }
    }
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

double Fourmi::distance(Point start, Point stop) {
    cout << "calling distance of an generic ant" << endl;
    return 0;
}

vector<Point> Fourmi::getNextMove(Point position) {
    cout << "calling getNextMove of an generic ant" << endl;
    return {};
}

vector<Point> Fourmi::findPath(Point start, Point stop) {
    vector<Point> initialDirection = getNextMove(start);
    vector<int> initialDir = evaluateBestsDirections(initialDirection, stop);
    vector<vector<Point>> allPath = {};
    for(auto directionPath:initialDir) {
        vector<Point> path = {start};
        int inertia = directionPath;
        double distanceToTarget = 2*g_max;
        int watchdog = 0;
        while(not(path[path.size()-1] == stop)) {
            watchdog++;
            if(watchdog==150){
                path = {};
                break;
            }
            vector<Point> possibleNextStepVec = getNextMove(path[path.size()-1]);
            if(inertia == -1) { //find a new direction if the distance stop decreasing
                vector<int> dir = evaluateBestsDirections(possibleNextStepVec, stop);
                if(dir.size() > 0) {
                    inertia = dir[0];
                } else {
                    path = {};
                    break;
                }
            } else { // try to continue in the same direction
                if(distanceToTarget < distance(possibleNextStepVec[inertia], stop)) {
                    inertia = -1; // if distance increase, find new direction
                } else {
                    distanceToTarget = distance(possibleNextStepVec[inertia], stop);
                    path.push_back(possibleNextStepVec[inertia]);
                }
            }
        }
        if(path.size()>0){
            allPath.push_back(path);
        }
    }
    return prunePaths(allPath);
}

vector<int> Fourmi::evaluateBestsDirections(vector<Point> directionToEval,
                                            Point target) {
    double lowestDistance = 2*g_max;
    double lowestDistanceAbs = 2*g_max; // a value that will always be greater
    int direction = 0;
    vector<int> bestNextMove={};
    for(auto possibleNextStep:directionToEval) {
        if(lowestDistance > distance(possibleNextStep, target)) {
            lowestDistance = distance(possibleNextStep, target);
            lowestDistanceAbs = Point::distanceAbs(possibleNextStep, target);
            bestNextMove.push_back(direction);
        } else if (lowestDistance == distance(possibleNextStep, target)) {
            if(lowestDistanceAbs>(Point::distanceAbs(possibleNextStep, target)+0.01)){
                lowestDistance = distance(possibleNextStep, target);
                lowestDistanceAbs=Point::distanceAbs(possibleNextStep, target);
                bestNextMove.push_back(direction);
            }
        }
        direction++;
    }
    return bestNextMove;
}

vector<Point> Fourmi::prunePaths(vector<vector<Point>> pathToEvalVec) {
    if(pathToEvalVec.size() < 1) {
        return {};
    } else {
        vector<Point> toReturn;
        int lowestOverlapScore=g_max*g_max;
        for(auto pathToEval:pathToEvalVec) {
            int overlapScore = 0;
            for(auto step:pathToEval) {
                overlapScore+=Squarecell::countOverlap(step, getWidth(), getHeight(),
                                                       anyCST, true);
            }
            if(overlapScore<lowestOverlapScore) {
                lowestOverlapScore = overlapScore;
                toReturn = pathToEval;
            }
        }
        return toReturn;
    }
}

Collector::Collector(Point position, int id, int age, bool carryFood ) :
                         Fourmi(position, age,fourmiCollectorCST,id,sizeC) {
    this->carryFood = carryFood;
}

void Collector::update(vector<shared_ptr<Entity>> &entityList) {
    age++;

    if(pathBuffer.size() != 0) {
        bool foodStillClosest = true;
        bool foodStillThere = Squarecell::countOverlap(
                        pathBuffer[pathBuffer.size() - 1], 1, 1, nourritureCST, true);
        vector<Point> foods = findFoods(entityList);
        if (foods.size() > 0) {
            if (Point::distanceAbs(getPosition(),
                                   pathBuffer[pathBuffer.size() - 1]) >
                Point::distanceAbs(getPosition(),
                                   Collector::findFoods(entityList)[0])) {
                foodStillClosest = false;
            }
        }
        if((not foodStillClosest) or (not foodStillThere)) {
            pathBuffer = {};
        }
    }
    if(pathBuffer.size() == 0) {
        vector<Point> foods = findFoods(entityList);
        if(carryFood) {
            Point positionCollector = (*occupiedSpace).getPosition();
            Point pointToGo = findHome(entityList);
            cout << pointToGo.getCoordX() << " " << pointToGo.getCoordY() << endl;
            pathBuffer = findPath(positionCollector, pointToGo);
            for (auto step:pathBuffer) {
                cout << step.getCoordX() << " " << step.getCoordY() << endl;
            }
        } else if(foods.size()>0) {
            Point positionCollector = (*occupiedSpace).getPosition();
            Point pointToGo = foods[0];
            cout << "looking for path"<< endl;
            pathBuffer = findPath(positionCollector, pointToGo);
            cout << "path found"<< endl;
        } else {
            // behaviour if no food available
        }
    }
    if(pathBuffer.size() != 0) {
        if(pathBuffer.size()>1) {
            step(entityList);
        } else {
            if(carryFood) {
                unloadFood(entityList);
                pathBuffer = {};
            } else {
                loadFood(entityList);
                pathBuffer = {};
            }
        }
    }
}

double Collector::distance(Point start, Point stop) {
    bool sameCaseFamily = ((((start.getCoordX()+start.getCoordY())%2 == 0) and
                          ((stop.getCoordX()+stop.getCoordY())%2 == 0)) or
                          (((start.getCoordX()+start.getCoordY())%2 == 1) and
                          ((stop.getCoordX()+stop.getCoordY())%2 == 1)));
    if(sameCaseFamily) {
        double deltaX = stop.getCoordX()-start.getCoordX();
        double deltaY = stop.getCoordY()-start.getCoordY();
        return max(abs(deltaX),abs(deltaY));
    } else {
        return INFINITY;
    }
}

vector<Point> Collector::getNextMove(Point position) {
    vector<Point> nextMoves = {};
    int XRight = position.getCoordX()+1;
    if(not Point::isCoordInRange(XRight)){
        XRight = position.getCoordX();
    }
    int Xleft = position.getCoordX()-1;
    if(not Point::isCoordInRange(Xleft)){
        Xleft = position.getCoordX();
    }
    int YTop = position.getCoordY()+1;
    if(not Point::isCoordInRange(YTop)){
        YTop = position.getCoordX();
    }
    int YBot = position.getCoordY()-1;
    if(not Point::isCoordInRange(YBot)){
        YBot = position.getCoordX();
    }
    nextMoves.push_back(Point(XRight, YTop));
    nextMoves.push_back(Point(Xleft, YBot));
    nextMoves.push_back(Point(XRight, YBot));
    nextMoves.push_back(Point(Xleft, YTop));

    return nextMoves;
}

vector<Point> Collector::findFoods(vector<shared_ptr<Entity>> &entityList) {
    int xOrigin = getPosition().getCoordX();
    int yOrigin = getPosition().getCoordY();
    Point positionCollector = getPosition();
    vector<Point> listOfFood = Entity::findSpecie(Point(xOrigin, yOrigin),
                                                  nourritureCST, entityList);
    vector<Point> listFoodCaseFamily; //liste specie meme couleur case
    //savoir si case noir ou blanche
    bool spot = false; //case noir
    if(!((xOrigin+yOrigin)%2 == 0)) {
        spot = true;
    }
    //classer les food qui sont sur meme couleur case
    for(auto food : listOfFood) {
        int x = food.getCoordX();
        int y = food.getCoordY();
        if((x+y)%2 == spot) {
            listFoodCaseFamily.push_back(food);
        }
    }
    vector<Point> newListTrie;
    newListTrie = Entity::trie(positionCollector, listFoodCaseFamily);
    if(newListTrie.size()>0) {
        return newListTrie;
    } else {
        return {};
    }
}

Point Collector::findHome(vector<shared_ptr<Entity>> &entityList) {
    vector<shared_ptr<Entity>> fourmilliere = Entity::findByID(id, entityList,
                                                         fourmilliereCST);
    if(fourmilliere.size()>0){
        int x = (*fourmilliere[0]).getPosition().getCoordX();
        int y = (*fourmilliere[0]).getPosition().getCoordY();
        int width = (*fourmilliere[0]).getWidth();
        int height = (*fourmilliere[0]).getHeight();
        bool spot = false; //case noir
        if(!((getPosition().getCoordX()+getPosition().getCoordY())%2 == 0)) {
            spot = true;
        }
        vector<Point> side = {};
        for(unsigned int i = x;i<=(x+width);i++) {
            for(unsigned int j = y;j<=(y+height);j++) {
                if((i+j)%2 == spot){
                    side.push_back(Point(i,j));
                }
            }
        }
        vector<Point> newListTrie;
        newListTrie = Entity::trie(getPosition(), side);
        if(newListTrie.size()>0){
            return newListTrie[0];
        }
    }
    cout << "no anthill with ID to unload" << endl;
    exit(0);
}


void Collector::unloadFood(vector<shared_ptr<Entity>> &entityList) {
    vector<shared_ptr<Entity>> entity = Entity::findByID(id, entityList,
                                                         fourmiGeneratorCST);
    if(entity.size()>0) {
        shared_ptr<Generator> gene = dynamic_pointer_cast<Generator>(entity[0]);
        gene->addFood();
        carryFood = false;
        pathBuffer.erase(pathBuffer.begin());
    } else {
        cout << "no generator with ID to unload" << endl;
        exit(0);
    }
}

void Collector::loadFood(vector<shared_ptr<Entity>> &entityList) {
    shared_ptr<Entity> food = Entity::findByPosition(pathBuffer[0],
                                                     entityList, nourritureCST);

    food->setEndOfLife(true);
    carryFood = true;
    pathBuffer.erase(pathBuffer.begin());
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
    if(!(inputBuffer.size() <= 4)) {
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
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeC, sizeC,
                                                       anyCST, true);
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (errorCode);
    }
    return make_shared<Collector> (Point(x,y), index, age, conditionFood);
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

Point Defensor::findClosestBorder(vector<shared_ptr<Entity>> &entityList) {
    //vector<shared_ptr<Entity>> anthill = Entity::findByID(getId(), entityList, fourmilliereCST);
    //Point cornerLeftBot = (*(*anthill[0]).getOccupiedSpace()).getHitboxBotLeft();
    //Point cornerRightTop = (*(*anthill[0]).getOccupiedSpace()).getHitboxTopRight();
    //int side = (*anthill[0]).getHeight();
    //int sideDivide = (*anthill[0]).getHeight()%2;
    //Point positionDefensor(getPosition().getCoordX(), getPosition().getCoordY());

    //double distanceInit = Point::distanceAbs(positionDefensor, Point(cornerLeftBot.getCoordX(),cornerLeftBot.getCoordY()+sideDivide));
    //if()

    return Point();
}

void Defensor::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    bool bordureStillClosest = false;
    bool bordureStillFree = false;
    if(pathBuffer.size() == 0) {
        // ici recalculer le chemin pour vers la bordure
        bordureStillClosest = true;
        bordureStillFree = true;
    } else { // ensure the we still have the best path
        bordureStillClosest =
          (Point::distanceAbs(getPosition(),pathBuffer[pathBuffer.size()-1]) <=
           Point::distanceAbs(getPosition(),Defensor::findClosestBorder(entityList)));
        bordureStillFree = (0==Squarecell::countOverlap(
                pathBuffer[pathBuffer.size() - 1], sizeD, sizeD,
                fourmiDefensorCST, true));
    }
    if(bordureStillClosest and bordureStillFree) { // if the path is still valid
        if(pathBuffer.size() > 1) { // walk toward the border one step at a time
            step(entityList);
        }
    }
}

double Defensor::distance(Point start, Point stop) {
    bool sameCaseFamily = ((((start.getCoordX()+start.getCoordY())%2 == 0) and
                            ((stop.getCoordX()+stop.getCoordY())%2 == 0)) or
                           (((start.getCoordX()+start.getCoordY())%2 == 1) and
                            ((stop.getCoordX()+stop.getCoordY())%2 == 1)));
    if(sameCaseFamily){
        double deltaX = stop.getCoordX()-start.getCoordX();
        double deltaY = stop.getCoordY()-start.getCoordY();
        return min(deltaX,deltaY);
    } else {
        return INFINITY;
    }
}

vector<Point> Defensor::getNextMove(Point position) {
    Point right = Point(position.getCoordX()+1,position.getCoordY());
    Point up =  Point(position.getCoordX(),position.getCoordY()+1);
    Point left = Point(position.getCoordX()-1,position.getCoordY());
    Point down = Point(position.getCoordX(),position.getCoordY()-1);
    return {right, up, left, down};
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
    if(!(inputBuffer.size() <= 3)) {
        cout << "Defensor : number of argument mismatch" << endl;
        throw (errorCode);
    } else {
    long int x = stoi(inputBuffer[0]);
    long int y = stoi(inputBuffer[1]);
    long int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeD, sizeD,
                                                       anyCST, true);
    if(overlapList.size() > 0) { // ensure the ant does not collide with something else
        cout<< message::defensor_overlap(x,y, overlapList[0].getCoordX(),
                                         overlapList[0].getCoordY());
        throw (errorCode);
    }
    return make_shared<Defensor>(Point(x,y), index, age);
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

Point Predator::findClosestEnemy(vector<shared_ptr<Entity>> &entityList) {
    return Point();
}

void Predator::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    bool bordureStillClosest = false;
    bool bordureStillFree = false;
    if(pathBuffer.size()==0) {
        // ici recalculer le chemin pour vers la bordure
        bordureStillClosest = true;
        bordureStillFree = true;
    } else { // ensure the we still have the best path
        bordureStillClosest =
           (Point::distanceAbs(getPosition(),pathBuffer[pathBuffer.size()-1]) <=
            Point::distanceAbs(getPosition(),Predator::findClosestEnemy(entityList)));
        bordureStillFree=(0==Squarecell::countOverlap(pathBuffer[pathBuffer.size()-1],
                                                      sizeD, sizeD,
                                                      fourmiDefensorCST, true));
    }
    if(bordureStillClosest and bordureStillFree) { // if the path is still valid
        if(pathBuffer.size() > 1) { // walk toward the border one step at a time
            step(entityList);
        }
    }
}

double Predator::distance(Point start, Point stop) {
    bool sameCaseFamily = ((((start.getCoordX()+start.getCoordY())%2 == 0) and
                            ((stop.getCoordX()+stop.getCoordY())%2 == 0)) or
                           (((start.getCoordX()+start.getCoordY())%2 == 1) and
                            ((stop.getCoordX()+stop.getCoordY())%2 == 1)));
    if(sameCaseFamily) {
        double deltaX = stop.getCoordX()-start.getCoordX();
        double deltaY = stop.getCoordY()-start.getCoordY();
        return min(deltaX,deltaY);
    } else {
        return INFINITY;
    }
}

vector<Point> Predator::getNextMove(Point position) {
    Point upRight = Point(position.getCoordX()+1,position.getCoordY()+1);
    Point upLeft = Point(position.getCoordX()-1,position.getCoordY()+1);
    Point downLeft = Point(position.getCoordX()-1,position.getCoordY()-1);
    Point downRight = Point(position.getCoordX()+1,position.getCoordY()-1);
    return {upRight, upLeft, downLeft, downRight};
}

void Predator::predatorMurderRadius() {
    Point up(getPosition().getCoordX(), getPosition().getCoordX() + 1);
    Point down(getPosition().getCoordX(), getPosition().getCoordY() - 1);
    Point right(getPosition().getCoordX() + 1, getPosition().getCoordY());
    Point left(getPosition().getCoordX() - 1, getPosition().getCoordY());

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
        vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeP, sizeP,
                                                           anyCST, true);
        if(overlapList.size()>0) { // ensure the ant does not collide with something
            cout<< message::predator_overlap(x,y);
            throw (errorCode);
        }
    return make_shared<Predator>(Point(x,y), index, age);
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

Point Generator::findCenter(vector<shared_ptr<Entity>> &entityList) {
    vector<shared_ptr<Entity>> anthill = Entity::findByID(getId(), entityList, fourmilliereCST);
    Point cornerLeftBot = (*(*anthill[0]).getOccupiedSpace()).getHitboxBotLeft();
    Point cornerRightTop = (*(*anthill[0]).getOccupiedSpace()).getHitboxTopRight();

    int deltaX = (cornerRightTop.getCoordX()-cornerLeftBot.getCoordX())/2;
    int deltaY = (cornerRightTop.getCoordY()-cornerLeftBot.getCoordY())/2;
    int centerX = cornerLeftBot.getCoordX() + deltaX;
    int centerY = cornerLeftBot.getCoordY() + deltaY;

    return Point(centerX, centerY);
}

void Generator::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    bool centerStillWhereExpected = false;
    if(pathBuffer.size()==0) {
        if(not(Generator::findCenter(entityList) == getPosition())) {
            Point positionGenerator = getPosition();
            Point pointToGo = findCenter(entityList);
            pathBuffer = findPath(positionGenerator, pointToGo);
            // recalculer le chemin pour vers le centre de la fourmilliere
        }
    } else { // ensure the we still have the best path
        centerStillWhereExpected =
                (Point::distanceAbs(getPosition(),pathBuffer[pathBuffer.size()-1]) <=
                 Point::distanceAbs(getPosition(),Generator::findCenter(entityList)));
    }
    if(centerStillWhereExpected) { // if the path is still valid
        if(pathBuffer.size() > 0) { // walk toward the border one step at a time
            step(entityList);
        }
    }
}

double Generator::distance(Point start, Point stop) {
    return Point::distanceAbs(start,stop);
}

vector<Point> Generator::getNextMove(Point position) {
    Point right = Point(position.getCoordX()+1,position.getCoordY());
    Point upRight = Point(position.getCoordX()+1,position.getCoordY()+1);
    Point up = Point(position.getCoordX(),position.getCoordY()+1);
    Point upLeft = Point(position.getCoordX()-1,position.getCoordY()+1);
    Point left = Point(position.getCoordX()-1,position.getCoordY());
    Point downLeft = Point(position.getCoordX()-1,position.getCoordY()-1);
    Point down = Point(position.getCoordX(),position.getCoordY()-1);
    Point downRight = Point(position.getCoordX()+1,position.getCoordY()-1);
    return {right, upRight, up, upLeft, left, downLeft, down, downRight};
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
        throw (errorCode);
    }
    return make_shared<Generator>(Point(x,y), index);
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
