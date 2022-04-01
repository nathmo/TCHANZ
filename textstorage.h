/*!
  \file   textstorage.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "textstorage".
*/
#ifndef TCHANZ_TEXTSTORAGE_H
#define TCHANZ_TEXTSTORAGE_H

#include "squarecell.h"
#include "nourriture.h"
#include "fourmiliere.h"
#include "entity.h"
#include <string>
#include <vector>
#include <memory>

namespace textstorage {
    void writetxt(std::string filename, std::vector<std::vector<std::string>> lineToWrite);
    std::vector<std::vector<std::string>> readtxt(std::string filename);
    std::vector<std::string> creation(std::string line);
    std::vector<std::shared_ptr<Entity>> importDump(std::vector<std::vector<std::string>> intArrayDump);
    void importDump(std::vector<std::vector<std::string>> inputBuffer,
                    std::vector<std::shared_ptr<nourriture::Nourriture>> &foodVectorReturn,
                    std::vector<std::shared_ptr<fourmiliere::Fourmiliere>> &fourmilliereVectorReturn);
    std::vector<std::vector<std::string>> exportDump(std::vector<std::shared_ptr<Entity>> entityArrayDump);
    bool checksize_line(std::vector<std::vector<std::string>> intArrayDump);
}

#endif //TCHANZ_TEXTSTORAGE_H