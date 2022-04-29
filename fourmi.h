/*!
  \file   fourmi.h
  \author Nathann Morand (80%) et Felipe Ramirez (20%)
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
    virtual void update(std::vector<std::shared_ptr<Entity>> & entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    void virtual draw();
};

class Collector : public Fourmi {
private:
    bool carryFood;

public:
    Collector(Point position, int id, int age, bool carryFood);
    virtual void update(std::vector<std::shared_ptr<Entity>> & entityList);
    std::vector<Point> bestPathCollector(Point positionCollector,
                                         Point newListTrie);
    void bestDiago(Point positionCollector, Point newListTrie, double distanceInit,
                   std::vector<Point> &path, int index, bool first, bool &stop);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveCollector(
                                    std::vector<std::string> &inputBuffer, int index);
    void virtual draw();
};

class Defensor : public Fourmi {
public:
    Defensor(Point position, int id, int age);
    virtual void update(std::vector<std::shared_ptr<Entity>> & entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveDefensor(
                                    std::vector<std::string> &inputBuffer, int index);
    void virtual draw();
};

class Predator : public Fourmi {
public:
    Predator(Point position, int id, int age);
    virtual void update(std::vector<std::shared_ptr<Entity>> & entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSavePredator(
                                    std::vector<std::string> &inputBuffer, int index);
    void virtual draw();
};

class Generator : public Fourmi {
public:
    Generator(Point position, int id);
    virtual void update(std::vector<std::shared_ptr<Entity>> & entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveGenerator(
                                    std::vector<std::string> &inputBuffer, int index);
    void virtual draw();
};

#endif //TCHANZ_FOURMI_H