/*!
  \file   nourriture.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "nourriture".
*/

#ifndef TCHANZ_NOURRITURE_H
#define TCHANZ_NOURRITURE_H

#include "squarecell.h"
#include "entity.h"
#include <memory>

namespace nourriture
{
    class Nourriture : public entity::Entity {
    public:
        Nourriture(squarecell::Point position, int index);
        static std::shared_ptr<entity::Entity> importFromExtSave(std::vector<std::string>& inputBuffer, int index);
    };
}
#endif //TCHANZ_NOURRITURE_H