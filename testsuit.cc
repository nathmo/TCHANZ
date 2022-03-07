/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/

#include <iostream>
#include "testsuit.h"
#include "textstorage.h"

using namespace std;

int main (void)
{
    assert_textstorage_readtxt();
    // add all test here (unit and integration + test where we read the scenario
    // file and play them

    return 0; // optionnel
}

bool assert_textstorage_readtxt()
{
    vector <string> testreadtxt = readtxt("scenario/no_error_collector_move.txt");
    for (auto testreadtxt:stringtxt)
    {
        cout << stringtxt << endl;
    }
    return true;
}