/*!
  \file   nourriture.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "nourriture".
*/

#include "nourriture.h"
#include "squarecell.h"
#include "constantes.h"
#include <memory>
#include <iostream>

using namespace std;

nourriture::Nourriture(squarecell::Point position) :
    squarecell::Entity(position, squarecell::Point(1,1), nourritureCST) {}

const shared_ptr<squarecell::Entity> nourriture::importFromExtSavet (vector<string>& inputBuffer)
{
    if(!(inputBuffer.size() <= 2)){
        cout << "nourriture : number of argument mismatch" << endl;
        exit(0);
    }else{
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        return make_shared<nourriture::Nourriture>(squarecell::Point(x,y));
    }
}