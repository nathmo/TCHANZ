/*!
  \file   simulation.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "simulation".
*/

#ifndef TCHANZ_SIMULATION_H
#define TCHANZ_SIMULATION_H

#include <string>
#include "entity.h"
#include <memory>
#include <vector>

class Simulation {

};

// administrative function outside of class
std::vector<std::shared_ptr<Entity>> loadFromFile(std::string path);
void saveToFile(std::string path,std::vector<std::shared_ptr<Entity>> worldToDump);

#endif //TCHANZ_SIMULATION_H