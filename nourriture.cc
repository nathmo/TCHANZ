/*!
  \file   nourriture.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "nourriture".
*/

#include "nourriture.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"
#include <memory>
#include <iostream>

using namespace std;

nourriture::Nourriture::Nourriture(squarecell::Point position, int index) :
        entity::Entity(position, 1, 1, nourritureCST, index) {}

shared_ptr<entity::Entity> nourriture::Nourriture::importFromExtSave(vector<string>& inputBuffer, int index)
{
    if(!(inputBuffer.size() <= 2))
    {
        cout << "nourriture : number of argument mismatch" << endl;
        exit(0);
    }else{
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        if(squarecell::Squarecell::checkOverlap(squarecell::Point(x,y), 1, 1, nourritureCST))
        {
            cout<< message::food_overlap(x,y);
            exit(EXIT_FAILURE);
        }
        return make_shared<nourriture::Nourriture>(squarecell::Point(x,y), index);
    }
}