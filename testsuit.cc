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
#include <string>

using namespace std;

string assert_textstorage_readtxt(vector<string>);
void assert_textstorage_writetxt(vector<string>);

int main() {
    cout << "test readtxt started" << endl;
    assert_textstorage_readtxt(readtxt("no_error_collector_move.txt"));
    cout << "test readtxt done" << endl;

    cout << "test writetxt started" << endl;
    assert_textstorage_writetxt(textToWrite); // j suis pas sur de comment tu veux faire rentrer ton vector de string fonction dans laquelle tu rentres a la main du coup avec des cin ?
    cout << "test writetxt done" << endl;

    return 0;
}

string assert_textstorage_readtxt(vector<string> inputBuffer) {  //t avais mis un vector de string, j pense un string mieux ?
    string teststringdebut = "# Simple test file without error";
    string teststringfin = "\t# predators:";

    if(teststringdebut == inputBuffer[0] and teststringfin == inputBuffer[inputBuffer.size() - 1]) {
        return "C'est tout bon teststorage_readtxt";
    } else {
        return "C'est pas bon teststorage_readtxt";
    }
}



void assert_textstorage_writetxt(vector<string> textToWrite) {      //t avais mis un bool de base
    //string teststring = "Notre phrase test";
    string Stockage_fichiertxt;

    writetxt(Stockage_fichiertxt, textToWrite);
    assert_textstorage_readtxt(Stockage_fichiertxt);

    // use la fonction write de textstorage et write dans un fichier text.txt
    // use la fonction read de textstorage et read dans le fichier text.txt qui viens d'etre ecrit
}
