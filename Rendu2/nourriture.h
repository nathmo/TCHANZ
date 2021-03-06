/*!
  \file   nourriture.h
  \author Nathann Morand (50%) et Felipe Ramirez (50%)
  \date   MARS 2022
  \brief  prototype du module "nourriture".
*/
#ifndef TCHANZ_NOURRITURE_H
#define TCHANZ_NOURRITURE_H

#include <memory>
#include <vector>
#include "squarecell.h"
#include "entity.h"

class Nourriture : public Entity {
public:
    Nourriture(Point position, int index);
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Nourriture> importFromExtSave(
                                    std::vector<std::string> &inputBuffer, int index);
    static std::shared_ptr<Nourriture> randomCreate();
    virtual void update(std::vector<std::shared_ptr<Entity>> &entityList);
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> exportToString();
    virtual void draw();
};

#endif //TCHANZ_NOURRITURE_H