/*!
  \file   fourmi.h
  \author Nathann Morand (80%) et Felipe Ramirez (20%)
  \date   MARS 2022
  \brief  prototype du module "fourmi".
*/
#ifndef TCHANZ_FOURMI_H
#define TCHANZ_FOURMI_H

#include <memory>
#include "squarecell.h"
#include "entity.h"

class Fourmi : public Entity {
protected:
int age;

public:
    Fourmi(Point position, int age, char type, int id, int size);
    virtual void update();
};

class Collector : public Fourmi {
private:
    bool carryFood;

public:
    Collector(Point position, int id, int age, bool carryFood);
    virtual void update();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveCollector(
            std::vector<std::string> &inputBuffer, int index);
};

class Defensor : public Fourmi {
public:
    Defensor(Point position, int id, int age);
    virtual void update();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveDefensor(
            std::vector<std::string> &inputBuffer, int index);
};

class Predator : public Fourmi {
public:
    Predator(Point position, int id, int age);
    virtual void update();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSavePredator(
            std::vector<std::string> &inputBuffer, int index);
};

class Generator : public Fourmi {
public:
    Generator(Point position, int id);
    virtual void update();
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Fourmi> importFromExtSaveGenerator(
                                    std::vector<std::string> &inputBuffer, int index);
};

#endif //TCHANZ_FOURMI_H