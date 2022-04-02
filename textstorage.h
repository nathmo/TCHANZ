/*!
  \file   textstorage.h
  \author Nathann Morand (10%) et Felipe Ramirez (90%)
  \date   MARS 2022
  \brief  prototype du module "textstorage".
*/
#ifndef TCHANZ_TEXTSTORAGE_H
#define TCHANZ_TEXTSTORAGE_H

#include <string>
#include <vector>
#include <memory>
#include "squarecell.h"
#include "nourriture.h"
#include "fourmiliere.h"
#include "entity.h"

class TextStorage {
public:
    static void writetxt(std::string filename, std::vector<std::vector<std::string>> lineToWrite);

    static std::vector<std::vector<std::string>> readtxt(std::string filename);

    static std::vector<std::string> creation(std::string line);

    static void importDump(std::vector<std::vector<std::string>> inputBuffer,
                    std::vector<std::shared_ptr<Nourriture>> &foodVectorReturn,
                    std::vector<std::shared_ptr<Fourmiliere>> &fourmilliereVectorReturn);

    static std::vector<std::vector<std::string>> exportDump(
            std::vector<std::shared_ptr<Entity>> entityArrayDump);

    static bool checksizeLine(std::vector<std::vector<std::string>> intArrayDump);

    static void importFood(std::vector<std::vector<std::string>> inputBuffer,
                           std::vector<std::shared_ptr<Nourriture>> &foodVectReturn);
};

#endif //TCHANZ_TEXTSTORAGE_H