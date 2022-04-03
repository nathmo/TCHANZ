/*!
  \file   nourriture.h
  \author Nathann Morand (50%) et Felipe Ramirez (50%)
  \date   MARS 2022
  \brief  prototype du module "nourriture".
*/
#ifndef TCHANZ_NOURRITURE_H
#define TCHANZ_NOURRITURE_H

#include <memory>
#include "squarecell.h"
#include "entity.h"

class Nourriture : public Entity {
public:
    Nourriture(Point position, int index);
    // create the object and return its pointer + check that it dont overlap something
    static std::shared_ptr<Nourriture> importFromExtSave(
            std::vector<std::string>& inputBuffer, int index);
    virtual void update();
    virtual std::vector<str::vector<std::string>> foodVecToExport(
                                            vector<shared_ptr<Entity>> &listOfEntity);
};

#endif //TCHANZ_NOURRITURE_H