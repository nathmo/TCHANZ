/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"

class Squarecell{
private:
    int g_max;
    vector<vector<bool>> grid(g_max, vector<bool>(g_max));

public:
    void setG_max(gmax){
        g_max = gmax;
    }
    int getG_max(){
        return gmax;
    }
    Squarecell(int gmax);
};
