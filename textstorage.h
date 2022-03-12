/*!
  \file   textstorage.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "textstorage".
*/
#ifndef TCHANZ_TEXTSTORAGE_H
#define TCHANZ_TEXTSTORAGE_H
#include "squarecell.h"
#include <string>
#include <vector>

namespace textstorage {
    void writetxt(std::string filename, std::vector<int> lineToWrite);
    std::vector<int> readtxt(std::string filename);
    std::vector<int> creation (std::string line);
    std::vector<squarecell::Entity> import (std::vector<int> intArrayDump);
}
#endif //TCHANZ_TEXTSTORAGE_H