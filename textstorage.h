//
// Created by felip on 06.03.2022.
//
#include <string>
#include <vector>
#ifndef TCHANZ_TEXTSTORAGE_H
#define TCHANZ_TEXTSTORAGE_H

#endif //TCHANZ_TEXTSTORAGE_H

namespace textstorage {
    void writetxt(string filename, vector <int> lineToWrite);
    std::vector<int> readtxt(string filename);
}