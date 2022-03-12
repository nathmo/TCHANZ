/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/

#include <iostream>
#include "textstorage.h"
#include "textstorage.cc"
#include <vector>
#include <string>

using namespace std;

bool assert_textstorage_readtxt();
bool assert_textstorage_writetxt();

int main() {
    assert(assert_textstorage_readtxt());
    assert(assert_textstorage_writetxt());
    cout << "test readtxt started" << endl;
    cout << (assert_textstorage_readtxt())<< endl;
    cout << "test readtxt done" << endl;

    cout << "test writetxt started" << endl;
    cout << (assert_textstorage_writetxt())<< endl; // j suis pas sur de comment tu veux faire rentrer ton vector de string fonction dans laquelle tu rentres a la main du coup avec des cin ?
    cout << "test writetxt done" << endl;

    return 0;
}

bool assert_textstorage_readtxt() {  //t avais mis un vector de string, j pense un string mieux ?
    int teststringfin = 0;
    vector <int> inputBuffer = readtxt_modifie_sans_espace("scenario/no_error_collector_move.txt");
    if(teststringfin == inputBuffer[inputBuffer.size() - 1]) {
        return true;
    } else {
        //cout << teststringfin <<endl;
        //cout << inputBuffer[inputBuffer.size() - 1] <<endl;
        return false;
    }
}



bool assert_textstorage_writetxt() {      //t avais mis un bool de base
    vector <int> teststring = {1234};
    string Stockage_fichiertxt = "test_ecriture.txt";

    textstorage::writetxt(Stockage_fichiertxt, teststring);
    vector <int> inputBuffer = readtxt(Stockage_fichiertxt);
    if(teststring[0] == inputBuffer[0] and teststring[0] == inputBuffer[inputBuffer.size() - 1]) {
        return true;
    } else {
        return false;
    }
}
