/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/

#include <iostream>
#include "testsuit.h"
#include "textstorage.h"
#include "textstorage.cc"
#include <vector>

using namespace std;

vector<string> assert_textstorage_readtxt();
bool copieWrite();

int main() {
    cout << "test started" << endl;
    copieWrite(assert_textstorage_readtxt());

    // add all test here (unit and integration + test where we read the scenario
    // file and play them
    cout << "test done" << endl;
    return 0; // optionnel
}

vector<string> assert_textstorage_readtxt() {
    vector<string> testreadtxt = readtxt("scenario/no_error_neighbours_anthill.txt");
    for (auto stringtxt:testreadtxt) {
        cout << stringtxt << endl;
    }
    return testreadtxt;
}

bool copieWrite(vector<string>) {
    fstream copie_Write = writetxt("scenario/no_error_neighbours_anthill.txt",  );
    for (auto element : copie_Write) {
        cout << element << endl;
    }
    return true;
}
