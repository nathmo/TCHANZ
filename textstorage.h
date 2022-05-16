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

namespace TextStorage {
    void importTXT(std::string filename,
                std::vector<std::shared_ptr<Nourriture>> &foodVectorReturn,
                std::vector<std::shared_ptr<Fourmiliere>> &fourmilliereVectorReturn);

    void exportTXT(std::string filename,
                std::vector<std::shared_ptr<Nourriture>> &foodVectorReturn,
                std::vector<std::shared_ptr<Fourmiliere>> &fourmilliereVectorReturn);
    // write a list of tokenized word to a file
    void writetxt(std::string filename,
                  std::vector<std::vector<std::string>> lineToWrite);
    // convert a file to a list of tokenized word
    std::vector<std::vector<std::string>> readtxt(std::string filename);

    std::vector<std::string> tokenize(std::string line);
    // convert the list of tokenized word to usable list of  entitys
    void importDump(std::vector<std::vector<std::string>> inputBuffer,
                 std::vector<std::shared_ptr<Nourriture>> &foodVectorReturn,
                 std::vector<std::shared_ptr<Fourmiliere>> &fourmilliereVectorReturn);
    // convert a list of entitys to a list of tokenized word
    std::vector<std::vector<std::string>> exportDump(
                                std::vector<std::shared_ptr<Entity>> entityArrayDump);
    // ensure the file is consistend
    bool checksizeLine(std::vector<std::vector<std::string>> listOfEntity);
    // used in importDump to import the food elements
    void importFood(std::vector<std::vector<std::string>> inputBuffer,
                    std::vector<std::shared_ptr<Nourriture>> &foodVectReturn);
}

#endif //TCHANZ_TEXTSTORAGE_H