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
            if(watchdog==250){
                path = {};
                break;
            }
            vector<Point> possibleNextStepVec = getNextMove(path[path.size()-1]);
            if(inertia == -1) { //find a new direction if the distance stop decreasing
                vector<int> dir = evaluateBestsDirections(possibleNextStepVec, stop);
                if(dir.size() > 0) {
                    inertia = dir[dir.size()-1];
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
            if(lowestDistanceAbs>(Point::distanceAbs(possibleNextStep, target)-0.01)){
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
    for(int i=0;i<10;i++) {
        int x = Entity::randInt(1,g_max-2);
        int y = Entity::randInt(1,g_max-2);
        if ((x+y)%2==(position.getCoordX()+position.getCoordY())%2){
            if(not Squarecell::checkOverlap(Point(x,y), sizeC, sizeC, allCST, true)) {
                pathBuffer = findPath(position, Point(x,y));
            }
        }
    }
}

void Collector::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    evaluateConditionTarget(entityList);
    if(pathBuffer.size() == 0) {
        recomputePath(entityList);
    }
    if(pathBuffer.size() != 0) {
        if(pathBuffer.size()>1) {
            step(entityList);
        } else {
            if(carryFood) {
                unloadFood(entityList);
            } else {
                loadFood(entityList);
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
    vector<Point> listOfFood = Entity::findSpecie(nourritureCST, entityList);
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
    vector<shared_ptr<Entity>> f = Entity::findByID(id, entityList, fourmilliereCST);
    if(f.size()>0){
        int x = (*(*f[0]).getOccupiedSpace()).getHitboxBotLeft().getCoordX();
        int y = (*(*f[0]).getOccupiedSpace()).getHitboxBotLeft().getCoordY();
        int width = (*f[0]).getWidth();
        int height = (*f[0]).getHeight();
        bool caseFamily = false; //case noir
        if((getPosition().getCoordX()+getPosition().getCoordY())%2) {
            caseFamily = true;
        }
        vector<Point> side = {};
        for(int j = y;j<(y+height);j++) {
            if((x+j)%2 == caseFamily){
                side.push_back(Point(x,j));
            }
            if((x+width+j)%2 == caseFamily){
                side.push_back(Point(x+width,j));
            }
        }
        for(int i = x;i<(x+width);i++) {
            if((i+y)%2 == caseFamily){
                side.push_back(Point(i,y));
            }
            if((i+height+y)%2 == caseFamily){
                side.push_back(Point(i+height,y));
            }
        }
        int lowestDistanceToHome = g_max*g_max;
        Point candidat;
        for(auto target:side){
            if(distance(getPosition(), target)<lowestDistanceToHome){
                lowestDistanceToHome = distance(getPosition(), target);
                candidat = target;
            }
        }
        return candidat;
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
        pathBuffer = {};
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
    pathBuffer = {};
}

void Collector::evaluateConditionTarget(vector<shared_ptr<Entity>> &entityList){
    if((pathBuffer.size() !=0) and (not carryFood)) {
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
}

void Collector::recomputePath(vector<shared_ptr<Entity>> &entityList) {
    vector<Point> foods = findFoods(entityList);
    int odd =0;
    int autre =0;
    for(auto f:foods){
        if((f.getCoordX()+f.getCoordY())%2){
            odd++;
        } else {
            autre++;
        }
    }
    if(carryFood) {
        Point positionCollector = (*occupiedSpace).getPosition();
        Point pointToGo = findHome(entityList);
        if((positionCollector.getCoordX() == pointToGo.getCoordX()) and
           (positionCollector.getCoordY() == pointToGo.getCoordY())){
            pathBuffer = {};
        } else {
            pathBuffer = findPath(positionCollector, pointToGo);
        }
    } else if(foods.size()>0) {
        Point positionCollector = (*occupiedSpace).getPosition();
        Point pointToGo = foods[0];
        if((positionCollector.getCoordX() == pointToGo.getCoordX()) and
           (positionCollector.getCoordY() == pointToGo.getCoordY())){
            pathBuffer = {};
        } else {
            pathBuffer = findPath(positionCollector, pointToGo);
        }
    } else {
        // behaviour if no food available
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
    if(!(inputBuffer.size() <= 4)) {
        cout << "Collector : number of argument mismatch" << endl;
        throw (errorCode);
    } else {
        long int x = stoi(inputBuffer[0]);
        long int y = stoi(inputBuffer[1]);
        int age = stoi(inputBuffer[2]);
        bool conditionFood = false;
        if("true" == inputBuffer[3]) {
            conditionFood = true;
        }
        vector<Point> overlapList = Squarecell::getOverlap(Point::checkPoint(x, y),
                                                          sizeC, sizeC, anyCST, true);
        if(overlapList.size()>0) { //ensure the ant dont collide with something else
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
    vector<shared_ptr<Entity>> anthill = Entity::findByID(getId(), entityList,
                                                          fourmilliereCST);
    Point lb=(*(*anthill[0]).getOccupiedSpace()).getHitboxBotLeft();
    Point rt=(*(*anthill[0]).getOccupiedSpace()).getHitboxTopRight();
    lb = Point(lb.getCoordX()+1, lb.getCoordY()+1);
    Point borderBoxLeftA=Point(lb.getCoordX(),lb.getCoordY()+3);
    Point borderBoxLeftB=Point(lb.getCoordX()+3,rt.getCoordY()-3);
    Point borderBoxDownA=Point(lb.getCoordX()+3,lb.getCoordY());
    Point borderBoxDownB=Point(rt.getCoordX()-3,lb.getCoordY()+3);
    Point borderBoxRightA=Point(rt.getCoordX()-3,lb.getCoordY()+3);
    Point borderBoxRightB=Point(rt.getCoordX(),lb.getCoordY()-3);
    Point borderBoxTopA=Point(lb.getCoordX()+3,rt.getCoordY()-3);
    Point borderBoxTopB=Point(rt.getCoordX()-3,rt.getCoordY());
    vector<vector<Point>> borderHorizontal = {{borderBoxDownA, borderBoxDownB},
                                              {borderBoxTopA, borderBoxTopB}};
    vector<vector<Point>> borderVertical = {{borderBoxLeftA, borderBoxLeftB},
                                            {borderBoxRightA, borderBoxRightB}};
    vector<Point> borderPoint = {};
    for(auto side:borderHorizontal){
        vector<Point> sidePoint = Squarecell::findFreeInArea(side[0], side[1],
                                                             sizeD, sizeD,
                                                             anyCST);
        borderPoint.insert(borderPoint.end(), sidePoint.begin(), sidePoint.end());
    }
    for(auto side:borderVertical){
        vector<Point> sidePoint = Squarecell::findFreeInArea(side[0], side[1],
                                                             sizeD, sizeD,
                                                             anyCST);
        borderPoint.insert(borderPoint.end(), sidePoint.begin(), sidePoint.end());
    }
    Point toReturn;
    int dist = g_max*g_max;
    for(auto border:borderPoint){
        if(distance(getPosition(), border)<dist) {
            dist = distance(getPosition(), border);
            toReturn = border;
        }
    }
    return toReturn;
}

void Defensor::update(vector<shared_ptr<Entity>> &entityList) {
    age++;
    evaluateConditionTarget(entityList);
    if(pathBuffer.size() == 0) {
        recomputePath(entityList);
    }
    if(pathBuffer.size() != 0) {
        step(entityList);
    }
    vector<shared_ptr<Entity>> fourmilliere = Entity::findByID(id, entityList,
                                                               fourmilliereCST);
    if(fourmilliere.size()>0){
        int width = (*fourmilliere[0]).getWidth();
        int height = (*fourmilliere[0]).getHeight();
        int overlap = Squarecell::countOverlap(getPosition(), sizeD, sizeD, true,
                              (*fourmilliere[0]).getPosition(), width, height, false);
        if(overlap < (sizeD*sizeD)){
            endOfLife = true;
        }
    }
}

void Defensor::evaluateConditionTarget(
                                    std::vector<std::shared_ptr<Entity>> &entityList){
    if(pathBuffer.size() != 0) {
        bool bordureStillClosest = (distance(getPosition(),
                                             pathBuffer[pathBuffer.size()-1]) <=
                                    distance(getPosition(),
                                             findClosestBorder(entityList)));
        if ((not bordureStillClosest)) {
            pathBuffer = {};
        }
    }
}

void Defensor::recomputePath(std::vector<std::shared_ptr<Entity>> &entityList){
    Point target = findClosestBorder(entityList);
    if((getPosition().getCoordX() == target.getCoordX()) and
       (getPosition().getCoordY() == target.getCoordY())){
        pathBuffer = {};
    } else {
        pathBuffer = findPath(getPosition(), target);
    }
}

double Defensor::distance(Point start, Point stop) {
    double deltaX = stop.getCoordX()-start.getCoordX();
    double deltaY = stop.getCoordY()-start.getCoordY();
    return abs(deltaX)+abs(deltaY);
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
    vector<Point> overlapList = Squarecell::getOverlap(Point::checkPoint(x,y),
                                                       sizeD, sizeD, anyCST, true);
    if(overlapList.size() > 0) { // ensure the ant dont collide with something else
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
    constrained = false;
}

void Predator::setConstrained(bool constrain){
    constrained = constrain;
}

vector<Point> Predator::findClosestEnemy(vector<shared_ptr<Entity>> &entityList) {
    vector<Point> listOfEnemyPos = {};
    for(auto enemy:entityList){
        if(enemy->getId() != int(id)){
            if((enemy->getSpecie()==fourmiCollectorCST) or
               (enemy->getSpecie()==fourmiCollectorCST)){
                listOfEnemyPos.push_back(enemy->getPosition());
            }
        }
    }
    if(not constrained){
        vector<shared_ptr<Entity>> fourmilliere = Entity::findByID(id, entityList,
                                                                   fourmilliereCST);
        if(fourmilliere.size()>0) {
            Point leftB=(*(*fourmilliere[0]).getOccupiedSpace()).getHitboxBotLeft();
            Point rightT=(*(*fourmilliere[0]).getOccupiedSpace()).getHitboxTopRight();
            int i=0;
            for(auto enemyPos:listOfEnemyPos){
                Point leftBEnemy=Point(enemyPos.getCoordX()-1,
                                       enemyPos.getCoordY()-1);
                Point rightTEnemy=Point(enemyPos.getCoordX()+1,
                                        enemyPos.getCoordY()+1);
                int isInAnthill = Squarecell::countOverlap(leftB, rightT,
                                                           leftBEnemy, rightTEnemy);
                if(not isInAnthill){
                    listOfEnemyPos.erase(listOfEnemyPos.begin()+i);
                    i--;
                }
                i++;
            }
        }
    }
    double closestEnemyDistance=2*g_max;
    vector<Point> closestEnemy={};
    for(auto enemyPos:listOfEnemyPos){
        if(closestEnemyDistance> distance(getPosition(), enemyPos)){
            closestEnemyDistance = distance(getPosition(), enemyPos);
            closestEnemy.push_back(enemyPos);
            break;
        }
    }
    return closestEnemy;
}

void Predator::update(vector<shared_ptr<Entity>> &entityList) {
    age++;

    if((pathBuffer.size() > 0)){
        Point oldTarget = pathBuffer[pathBuffer.size()-1];
        vector<Point> target = findClosestEnemy(entityList);
        bool targetmoved = true;
        if(target.size()>0){
            targetmoved = ((oldTarget.getCoordX() != target[0].getCoordX()) or
                                (oldTarget.getCoordY() != target[0].getCoordY()));
        }
        if(targetmoved){
            pathBuffer = {};
        }
    }

    if(pathBuffer.size()==0) {
        vector<Point> target = findClosestEnemy(entityList);
        if((pathBuffer.size() > 0)) {
            pathBuffer = findPath(getPosition(), target[0]);
        }
    }
    if(pathBuffer.size() > 0) { // walk toward the border one step at a time
        if(pathBuffer.size() == 1){
            MurderRadius(entityList);
        } else {
            step(entityList);
        }
    }
}

double Predator::distance(Point start, Point stop) {
    return Point::distanceAbs(start, stop);
}

vector<Point> Predator::getNextMove(Point position) {
    Point upRightA = Point(position.getCoordX()+2,position.getCoordY()+1);
    Point upLeftA = Point(position.getCoordX()-2,position.getCoordY()+1);
    Point downLeftA = Point(position.getCoordX()-2,position.getCoordY()-1);
    Point downRightA = Point(position.getCoordX()+2,position.getCoordY()-1);
    Point upRightB = Point(position.getCoordX()+1,position.getCoordY()+2);
    Point upLeftB = Point(position.getCoordX()-1,position.getCoordY()+2);
    Point downLeftB = Point(position.getCoordX()-1,position.getCoordY()-2);
    Point downRightB = Point(position.getCoordX()+1,position.getCoordY()-2);
    return {upRightA, upLeftA, downLeftA, downRightA,
            upRightB, upLeftB, downLeftB, downRightB};
}

void Predator::MurderRadius(vector<shared_ptr<Entity>> &entityList) {
    Point center = getPosition();
    Point up(getPosition().getCoordX(), getPosition().getCoordX() + 1);
    Point down(getPosition().getCoordX(), getPosition().getCoordY() - 1);
    Point right(getPosition().getCoordX() + 1, getPosition().getCoordY());
    Point left(getPosition().getCoordX() - 1, getPosition().getCoordY());
    vector<Point> murderZone = {center, up, down, right, left};
    for(auto zone:murderZone){
        shared_ptr<Entity> victim = Entity::findByPosition(zone, entityList,
                                            (fourmiCollectorCST | fourmiPredatorCST));
        if(victim->getId() != int(id)){
            victim->setEndOfLife(true);
        }
        if(victim->getSpecie()==fourmiPredatorCST){
            endOfLife = true;
        }
    }
    pathBuffer = {};
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
        long int x = stoi(inputBuffer[0]);
        long int y = stoi(inputBuffer[1]);
        int age = stoi(inputBuffer[2]);
        vector<Point> overlapList = Squarecell::getOverlap(Point::checkPoint(x,y),
                                                          sizeP, sizeP, anyCST, true);
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
    vector<shared_ptr<Entity>> anthill = Entity::findByID(getId(), entityList,
                                                          fourmilliereCST);
    Point cornerLeftBot = (*(*anthill[0]).getOccupiedSpace()).getHitboxBotLeft();
    Point cornerRightTop = (*(*anthill[0]).getOccupiedSpace()).getHitboxTopRight();
    int deltaX = (cornerRightTop.getCoordX()-cornerLeftBot.getCoordX())/2;
    int deltaY = (cornerRightTop.getCoordY()-cornerLeftBot.getCoordY())/2;
    if((cornerRightTop.getCoordX()-cornerLeftBot.getCoordX())<13){
        if((cornerLeftBot.getCoordX()+deltaX)>(g_max/2)) { // right side of board
            deltaX = (cornerRightTop.getCoordX() - cornerLeftBot.getCoordX()) - 3;
        } else {
            deltaX = (cornerRightTop.getCoordX()-cornerLeftBot.getCoordX())-6;
        }
        if((cornerLeftBot.getCoordY()+deltaY)>(g_max/2)){ // top side of board
            deltaY = (cornerRightTop.getCoordY()-cornerLeftBot.getCoordY())-3;
        } else {
            deltaY = (cornerRightTop.getCoordY()-cornerLeftBot.getCoordY())-6;
        }
        deltaY = (cornerRightTop.getCoordY()-cornerLeftBot.getCoordY())-6;
    }
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
    vector<shared_ptr<Entity>> fourmilliere = Entity::findByID(id, entityList,
                                                               fourmilliereCST);
    if(fourmilliere.size()>0){
        int width = (*fourmilliere[0]).getWidth();
        int height = (*fourmilliere[0]).getHeight();
        int overlap = Squarecell::countOverlap(getPosition(), sizeG, sizeG, true,
                                               (*fourmilliere[0]).getPosition(), width, height, false);
        if(overlap < (sizeG*sizeG)){
            endOfLife = true;
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
    long int x = stoi(inputBuffer[3]);
    long int y = stoi(inputBuffer[4]);
    vector<Point> overlapList = Squarecell::getOverlap(Point::checkPoint(x,y), sizeG,
                                                       sizeG, anyCST, true);
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
