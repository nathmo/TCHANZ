/*!
  \file   simulation.h
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  prototype du module "simulation".
*/
#ifndef TCHANZ_SIMULATION_H
#define TCHANZ_SIMULATION_H

#include <string>
#include <memory>
#include <vector>
#include "entity.h"

class Simulation {

};

// administrative function outside of class
std::vector<std::shared_ptr<Entity>> loadFromFile(std::string path);
void saveToFile(std::string path,std::vector<std::shared_ptr<Entity>> worldToDump);

#endif //TCHANZ_SIMULATION_H