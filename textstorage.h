//
// Created by felip on 06.03.2022.
//
#include <string>
#include <vector>

#ifndef TCHANZ_TEXTSTORAGE_H
#define TCHANZ_TEXTSTORAGE_H

#endif //TCHANZ_TEXTSTORAGE_H

namespace textstorage {
    void writetxt(std::string filename, std::vector<std::string> lineToWrite);
    std::vector<int> readtxt(std::string filename);
    std::vector<int> creation (std::string line);
}