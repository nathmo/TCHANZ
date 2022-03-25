/*!
  \file   nourriture.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "nourriture".
*/

#ifndef TCHANZ_NOURRITURE_H
#define TCHANZ_NOURRITURE_H

#include "squarecell.h"
#include <memory>

namespace nourriture
{
    class Nourriture : public squarecell::Entity
    {
    public:
        Nourriture(squarecell::Point position);
        shared_ptr<squarecell::Entity> importFromExtSave const(std::vector<std::string>& inputBuffer));
    };
}
#endif //TCHANZ_NOURRITURE_H