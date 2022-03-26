/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/

#include "textstorage.h"
#include "squarecell.h"
#include "constantes.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <array>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <assert.h>
#include <memory>

using namespace std;


bool assert_textstorage();
bool assert_squarecell();
bool assert_textstorage_readtxt();
bool assert_textstorage_writetxt();
bool assert_squarecell_Point();
bool assert_squarecell_Entity();
bool assert_squarecell_checkOverlap(); //not implemented yet
bool assert_squarecell_Squarecell();
bool assert_squarecell_add();
bool assert_squarecell_remove();
bool assert_squarecell_checkSize();
bool assert_squarecell_checkHitbox();
bool assert_squarecell_checkOverlap2();
bool assert_squarecell_getHitboxBotLeft();
bool assert_squarecell_getHitboxTopRight();
bool assert_files_test();
string runCommand(const char* command);
bool stringFuzzyMatch(string str1, string str2);

int main() {
    cout << "beginning unit test" << endl;
    assert(assert_textstorage());
    assert(assert_squarecell());
    cout << "beginning integration test" << endl;
    assert(assert_files_test());
    cout << "all test passed successfully" << endl;
    return 0;
}

bool assert_textstorage() {
    assert(assert_textstorage_readtxt());
    assert(assert_textstorage_writetxt());
    cout << "-> textstorage done" << endl;
    return true;
}

bool assert_squarecell() {
    assert(assert_squarecell_Point());
    assert(assert_squarecell_Entity());
    assert(assert_squarecell_checkOverlap()); //not implemented yet
    assert(assert_squarecell_Squarecell());
    assert(assert_squarecell_add());
    assert(assert_squarecell_remove());
    assert(assert_squarecell_checkSize());
    assert(assert_squarecell_checkHitbox());
    assert(assert_squarecell_checkOverlap());
    assert(assert_squarecell_getHitboxBotLeft());
    assert(assert_squarecell_getHitboxTopRight());
    cout << "-> squarecell done" << endl;
    return true;
}

bool assert_textstorage_readtxt() {  //t avais mis un vector de string, j pense un string mieux ?
    string teststringfin = "0";
    vector<vector<string>> inputBuffer = textstorage::readtxt("scenario/no_error_collector_move.txt");
    if(teststringfin == inputBuffer[inputBuffer.size() - 1][inputBuffer[inputBuffer.size() - 1].size() - 1]) {
        return true;
    } else {
        cout << "expected : " << teststringfin <<endl;
        cout << "got : " << inputBuffer[inputBuffer.size() - 1][inputBuffer[inputBuffer.size() - 1].size() - 1] <<endl;
        cout << "number of line : " << inputBuffer.size() << endl;
        cout << "number of entry for this line 1 : " << inputBuffer[0].size() << endl;
        cout << "number of entry for this line 2 : " << inputBuffer[1].size() << endl;
        cout << "number of entry for this line 3 : " << inputBuffer[2].size() << endl;
        for (unsigned int i=0;i<inputBuffer[2].size();i++)
        {
            cout << inputBuffer[2][i] <<" "<< endl;
        }
        return false;
    }
}


bool assert_textstorage_writetxt() {      //t avais mis un bool de base
    vector<vector <string>> teststring = {{"1","2","3"},{"4","560000","-6","2"}};
    string Stockage_fichiertxt = "scenario/test_ecriture.txt";
    textstorage::writetxt(Stockage_fichiertxt, teststring);
    vector<vector<string>> inputBuffer = textstorage::readtxt(Stockage_fichiertxt);
    bool passed = true;
    for(unsigned int i=0; i<teststring.size();i++)
    {
        for(unsigned int j=0; j<teststring[i].size();j++)
        {
            if (teststring[i][j] != inputBuffer[i][j]) {
                passed = false;
            }
        }
    }
    if(passed)
    {
        return true;
    } else {
        cout << "expected : " + (teststring[0][0]) << endl;
        cout << "received : " + (inputBuffer[0][0]) << endl;
        cout << "expected : " + (teststring[0][2]) << endl;
        cout << "received : " + (inputBuffer[0][2]) << endl;
        cout << "expected : " + (teststring[1][2]) << endl;
        cout << "received : " + (inputBuffer[1][2]) << endl;
        cout << "expected : " + (teststring[1][3]) << endl;
        cout << "received : " + (inputBuffer[1][3]) << endl;
        return false;
    }
}

bool assert_squarecell_Point()
{
    squarecell::Point testPoint = squarecell::Point(1,3);
    assert(testPoint.getCoordX()==1);
    assert(testPoint.getCoordY()==3);
    return true;
}
bool assert_squarecell_Entity()
{
    shared_ptr<squarecell::Entity> testEnt = make_shared<squarecell::Entity>(squarecell::Point(2,4),squarecell::Point(1,2),'F');
    assert((*testEnt).getsize().getCoordX()==1);
    assert((*testEnt).getsize().getCoordY()==2);
    assert((*testEnt).getPosition().getCoordX()==2);
    assert((*testEnt).getPosition().getCoordY()==4);
    (*testEnt).setPosition(squarecell::Point(5,6));
    assert((*testEnt).getPosition().getCoordX()==5);
    assert((*testEnt).getPosition().getCoordY()==6);
    (*testEnt).setsize(squarecell::Point(4,8));
    assert((*testEnt).getsize().getCoordX()==4);
    assert((*testEnt).getsize().getCoordY()==8);
    assert((*testEnt).getSpecie()=='F');
    return true;
}
bool assert_squarecell_checkOverlap()
{
    return true;
}//not implemented yet
bool assert_squarecell_Squarecell()
{
    squarecell::Squarecell testSqCll = squarecell::Squarecell();
    shared_ptr<squarecell::Entity> testEnt = make_shared<squarecell::Entity>(squarecell::Point(2,4),squarecell::Point(2,2),fourmiCST);
    assert(testSqCll.add(testEnt));
    testEnt = make_shared<squarecell::Entity>(squarecell::Point(-100,-100),squarecell::Point(2,2),fourmiCST);
    assert(not(testSqCll.add(testEnt)));
    testEnt = make_shared<squarecell::Entity>(squarecell::Point(900,100),squarecell::Point(2,2),fourmiCST);
    assert(not(testSqCll.add(testEnt)));
    testEnt = make_shared<squarecell::Entity>(squarecell::Point(126,0),squarecell::Point(4,4),fourmiCST);
    assert(not(testSqCll.add(testEnt)));
    testEnt = make_shared<squarecell::Entity>(squarecell::Point(126,0),squarecell::Point(3,3),fourmiCST);
    assert(not(testSqCll.add(testEnt)));
    testEnt = make_shared<squarecell::Entity>(squarecell::Point(126,0),squarecell::Point(4,4),fourmiCST);
    assert(not(testSqCll.add(testEnt)));
    testEnt = make_shared<squarecell::Entity>(squarecell::Point(128,50),squarecell::Point(-3,-3),fourmiCST);
    assert(not(testSqCll.add(testEnt)));
    return true;
}
bool assert_squarecell_add()
{
    squarecell::Squarecell testSqCll = squarecell::Squarecell();
    shared_ptr<squarecell::Entity> testEnt = make_shared<squarecell::Entity>(squarecell::Point(20,40),squarecell::Point(3,3),fourmiCST);
    assert(testSqCll.add(testEnt));
    testSqCll.displayRawEntityGrid();
    return true;
}
bool assert_squarecell_remove()
{
    squarecell::Squarecell testSqCll = squarecell::Squarecell();
    shared_ptr<squarecell::Entity> testEnt = make_shared<squarecell::Entity>(squarecell::Point(20,40),squarecell::Point(3,3),fourmiCST);
    assert(testSqCll.add(testEnt));
    assert(testSqCll.remove(testEnt));
    assert(testSqCll.add(testEnt));
    testSqCll.displayRawEntityGrid();
    return true;
}
bool assert_squarecell_checkSize()
{
    return true;
}
bool assert_squarecell_checkHitbox()
{
    return true;
}
bool assert_squarecell_checkOverlap2()
{
    return true;
}
bool assert_squarecell_getHitboxBotLeft()
{
    return true;
}
bool assert_squarecell_getHitboxTopRight()
{
    return true;
}

bool assert_files_test()
{
    cout << runCommand("make build") << endl;
    string cmdExpected = "Please provide a file to load";
    string cmdResult =runCommand("./projet ");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cmdExpected = "";
    cmdResult = runCommand("./projet scenario/no_error_collector_move.txt");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    return true;
}

bool stringFuzzyMatch(string str1, string str2)
{
    if(!str1.empty()) {
        if (str1[str1.length() - 1] == '\n') {
            str1.erase(str1.length() - 1);
        }
    }
    if(!str2.empty()) {
        if (str2[str2.length() - 1] == '\n') {
            str2.erase(str2.length() - 1);
        }
    }
    if (not(str2 == str1))
    {
        cout << "str1 :"+str1<<endl;
        cout << "str2 :"+str2<<endl;
    }
    return (str2 == str1);
}

string runCommand(const char* command) {
    string result;
    array<char, 128> outputBuffer;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) {
        cout << "command failed" << endl;
        exit(0);
    }
    while (fgets(outputBuffer.data(), outputBuffer.size(), pipe.get()) != nullptr) {
        result += outputBuffer.data();
    }
    return result;
}

