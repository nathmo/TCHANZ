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
    string teststringdebut = "salut test! \n test";
    string teststringfin = "salut test! \n test";
}

bool assert_textstorage_writetxt() {
    string teststring = "salut test! \n test";
    // use la fonction write de textstorage et write dans un fichier text.txt
    // use la fonction read de textstorage et read dans le fichier text.txt qui viens d'etre ecrit
}
