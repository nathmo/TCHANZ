/*!
  \file   world.h
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   AVRIL 2022
  \brief  prototype du module "world".
*/

#ifndef TCHANZ_WORLD_H
#define TCHANZ_WORLD_H

#include <string>
#include <memory>
#include <vector>
#include "entity.h"
#include "nourriture.h"
#include "fourmiliere.h"

class World{
private:
    std::vector<std::shared_ptr<Nourriture>> nourritureList;
    std::vector<std::shared_ptr<Fourmiliere>> anthillList;
public:
    World();
    void addEntity(std::shared_ptr<Entity> entity);
    void delEntity(std::shared_ptr<Entity> entity);
};

#endif //TCHANZ_WORLD_H
