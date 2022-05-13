/*!
  \file   fourmi.h
  \author Nathann Morand (40%) et Felipe Ramirez (60%)
  \date   MARS 2022
  \brief  prototype du module "fourmi".
*/
#ifndef TCHANZ_FOURMI_H
#define TCHANZ_FOURMI_H

#include <memory>
#include <vector>
#include "squarecell.h"
#include "entity.h"

class Fourmi : public Entity {
protected:
    int age;
    std::vector<Point> pathBuffer;

public:
    Fourmi(Point position, int age, char type, int id, int size);
    int getAge();
    void step(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    virtual void draw();
    virtual double distance(Point start, Point stop);
    virtual std::vector<Point> getNextMove(Point position);
    std::vector<int> evaluateBestsDirections(std::vector<Point> directionToEval,
                                             Point target);
    std::vector<Point> prunePaths(std::vector<std::vector<Point>> pathToEvalVec);
    std::vector<Point> findPath(Point start, Point stop);
};

class Collector : public Fourmi {
private:
    bool carryFood;

public:
    Collector(Point position, int id, int age, bool carryFood);
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual double distance(Point start, Point stop);
    virtual std::vector<Point> getNextMove(Point position);

    std::vector<Point> findFoods(std::vector<std::shared_ptr<Entity>> &entityList);

    Point findHome(std::vector<std::shared_ptr<Entity>> &entityList);

    void unloadFood(std::vector<std::shared_ptr<Entity>> &entityList);

    void loadFood(std::vector<std::shared_ptr<Entity>> &entityList);

    void evaluateConditionTarget(std::vector<std::shared_ptr<Entity>> &entityList);
    void recomputePath(std::vector<std::shared_ptr<Entity>> &entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveCollector(
                                    std::vector<std::string> &inputBuffer, int index);
    virtual void draw();
};

class Defensor : public Fourmi {
public:
    Defensor(Point position, int id, int age);
    Point findClosestBorder(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual double distance(Point start, Point stop);
    virtual std::vector<Point> getNextMove(Point position);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveDefensor(
                                    std::vector<std::string> &inputBuffer, int index);
    virtual void draw();
};

class Predator : public Fourmi {
public:
    Predator(Point position, int id, int age);
    Point findClosestEnemy(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual double distance(Point start, Point stop);
    virtual std::vector<Point> getNextMove(Point position);
    void predatorMurderRadius();
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSavePredator(
                                    std::vector<std::string> &inputBuffer, int index);
    virtual void draw();
};

class Generator : public Fourmi {
private:
    int foodReceived;

public:
    Generator(Point position, int id);
    Point findCenter(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    virtual double distance(Point start, Point stop);
    virtual std::vector<Point> getNextMove(Point position);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveGenerator(
                                    std::vector<std::string> &inputBuffer, int index);
    virtual void draw();
    int getFood();
    void addFood();
    void removeFood();
};

#endif //TCHANZ_FOURMI_H