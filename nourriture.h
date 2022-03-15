/*!
  \file   nourriture.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "nourriture".
*/

#ifndef TCHANZ_NOURRITURE_H
#define TCHANZ_NOURRITURE_H

#import "squarecell.h"

namespace nourriture
{
    class Nourriture : public squarecell::Entity
    {
    public:
        Nourriture(squarecell::Point position);i
    };
}
#endif //TCHANZ_NOURRITURE_H