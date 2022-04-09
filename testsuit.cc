/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <array>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <assert.h>
#include <memory>
#include "textstorage.h"
#include "squarecell.h"
#include "constantes.h"
#include "entity.h"
#include "simulation.h"
#include "fourmiliere.h"

using namespace std;

bool assertTextstorage();
bool assertSquarecell();
bool assertEntity();
bool assertFourmi();
bool assertFourmilliere();
bool assertNourriture();
bool assertImportExport();

bool assertTextstorageReadtxt();
bool assertTextstorageWritetxt();

bool assertSquarecellPoint();
bool assertEntityEntity();
bool assertSquarecellSquarecell();
bool assertSquarecell();

bool assertFilesTest();
string runCommand(const char* command);
bool stringFuzzyMatch(string str1, string str2);

int main()
{
    cout << "---------------------------------------------------------------" << endl;
    cout << "beginning unit test" << endl;
    cout << "---------------------------------------------------------------" << endl;
    assert(assertTextstorage());
    assert(assertSquarecell());
    assert(assertEntity());
    assert(assertFourmi());
    assert(assertFourmilliere());
    assert(assertNourriture());
    assert(assertImportExport());
    cout << "---------------------------------------------------------------" << endl;
    cout << "beginning integration test" << endl;
    cout << "---------------------------------------------------------------" << endl;
    assert(assertFilesTest());
    cout << "---------------------------------------------------------------" << endl;
    cout << "all test passed successfully" << endl;
    cout << "---------------------------------------------------------------" << endl;
    return 0;
}

bool assertTextstorage()
{
    assert(assertTextstorageReadtxt());
    assert(assertTextstorageWritetxt());
    cout << "-> textstorage done" << endl;
    return true;
}

bool assertSquarecell()
{
    assertSquarecellPoint();
    cout << "-> Squarecell done" << endl;
    return true;
}

bool assertEntity()
{
    assertEntityEntity();
    cout << "-> Entity done" << endl;
    return true;
}
bool assertFourmi()
{
    cout << "-> Fourmi done" << endl;
    return true;
}
bool assertFourmilliere()
{
    cout << "-> Fourmilliere done" << endl;
    return true;
}
bool assertNourriture()
{
    cout << "-> Nourriture done" << endl;
    return true;
}

bool assertImportExport()
{
    string path = "scenario/t16.txt";
    vector<shared_ptr<Entity>> entityList;
    vector<shared_ptr<Nourriture>> nourritureList;
    vector<shared_ptr<Fourmiliere>> anthillList;
    TextStorage::importTXT(path, nourritureList, anthillList);

    entityList.insert(entityList.end(), nourritureList.begin(), nourritureList.end());
    entityList.insert(entityList.end(), anthillList.begin(), anthillList.end());

    vector<vector<string>> exportation = TextStorage::exportDump(entityList);
/*
    for(auto element : exportation) {
        for(auto element2 : element) {
            cout << element2 << " ";
        }
        cout << endl;
    }
*/
    cout << "-> Import and Export done" << endl;
    return true;
}

bool assertTextstorageReadtxt()
{
    string teststringfin = "0";
    vector<vector<string>> inputBuffer = TextStorage::readtxt("scenario/no_error_collector_move.txt");
    if(teststringfin == inputBuffer[inputBuffer.size() - 1][inputBuffer[inputBuffer.size() - 1].size() - 1])
    {
        return true;
    } else {
        cout << "expected : " << teststringfin <<endl;
        cout << "got : " << inputBuffer[inputBuffer.size() - 1][inputBuffer[inputBuffer.size() - 1].size() - 1] <<endl;
        cout << "number of line : " << inputBuffer.size() << endl;
        cout << "number of entry for this line 1 : " << inputBuffer[0].size() << endl;
        cout << "number of entry for this line 2 : " << inputBuffer[1].size() << endl;
        cout << "number of entry for this line 3 : " << inputBuffer[2].size() << endl;
        for(unsigned int i=0;i<inputBuffer[2].size();i++)
        {
            cout << inputBuffer[2][i] <<" "<< endl;
        }
        return false;
    }
}

bool assertTextstorageWritetxt()
{
    vector<vector<string>> teststring = {{"1","2","3"},{"4","560000","-6","2"}};
    string Stockage_fichiertxt = "scenario/test_ecriture.txt";
    TextStorage::writetxt(Stockage_fichiertxt, teststring);
    vector<vector<string>> inputBuffer = TextStorage::readtxt(Stockage_fichiertxt);
    bool passed = true;
    for(unsigned int i=0; i<teststring.size();i++)
    {
        for(unsigned int j=0; j<teststring[i].size();j++)
        {
            if(teststring[i][j] != inputBuffer[i][j])
            {
                passed = false;
            }
        }
    }
    if(passed)
    {
        return true;
    }else{
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

bool assertSquarecellPoint()
{
    Point testPoint = Point(1,3);
    assert(testPoint.getCoordX()==1);
    assert(testPoint.getCoordY()==3);
    return true;
}

bool assertEntityEntity()
{
    shared_ptr<Entity> testEnt = make_shared<Entity>(Point(2,4),1,1,'F',0);
    assert((*testEnt).getHeight()==1);
    assert((*testEnt).getWidth()==1);
    assert((*testEnt).getPosition().getCoordX()==2);
    assert((*testEnt).getPosition().getCoordY()==4);
    (*testEnt).setPosition(Point(5,6));
    assert((*testEnt).getPosition().getCoordX()==5);
    assert((*testEnt).getPosition().getCoordY()==6);
    (*testEnt).setSize(4,8);
    assert((*testEnt).getHeight()==4);
    assert((*testEnt).getWidth()==8);
    assert((*testEnt).getSpecie()=='F');
    return true;
}

bool assertFilesTest()
{
    cout << runCommand("make build") << endl; // force normal rebuild

    string cmdExpected;
    string cmdResult;
    /*
    cout << "test 1 starting (./projet)" << endl;
    cmdExpected = "Please provide a file to load";
    cmdResult =runCommand("./projet ");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 1 passed " << endl;
    */
    cout << "test 2 starting (./projet scenario/no_error_collector_move.txt --headless)" << endl;
    cmdExpected = "Correct file";
    cmdResult = runCommand("./projet scenario/no_error_collector_move.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 2 passed " << endl;

    cout << "test 3 starting (./projet scenario/no_error_neighbours_anthill.txt --headless)" << endl;
    cmdExpected = "Correct file";
    cmdResult = runCommand("./projet scenario/no_error_neighbours_anthill.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 3 passed " << endl;

    cout << "test 4 starting (./projet scenario/error_collector_overlap.txt --headless)" << endl;
    cmdExpected = "collector with coordinates 14 18 overlaps with another exclusive entity at least on 15 17";
    cmdResult = runCommand("./projet scenario/error_collector_overlap.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 4 passed " << endl;

    cout << "test 5 starting (./projet scenario/error_defensor_not_within_home.txt --headless)" << endl;
    cmdExpected = "defensor with coordinates 101 117 is not fully within its home: 0";
    cmdResult = runCommand("./projet scenario/error_defensor_not_within_home.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 5 passed " << endl;

    cout << "test 6 starting (./projet scenario/error_homes_overlap.txt --headless)" << endl;
    cmdExpected = "home 0 overlaps with home 1";
    cmdResult = runCommand("./projet scenario/error_homes_overlap.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 6 passed" << endl;

    cout << "test 7 starting (./projet scenario/error_homes_overlap.txt --headless)" << endl;
    cmdExpected = "home 0 overlaps with home 1";
    cmdResult = runCommand("./projet scenario/error_homes_overlap.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 7 passed" << endl;

    cout << "test 8 starting (./projet scenario/t01.txt --headless)" << endl;
    cmdExpected = "collector with coordinates 14 18 overlaps with another exclusive entity at least on 15 17";
    cmdResult = runCommand("./projet scenario/t01.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 8 passed" << endl;

    cout << "test 9 starting (./projet scenario/t02.txt --headless)" << endl;
    cmdExpected = "collector with coordinates 18 14 overlaps with another exclusive entity at least on 17 15";
    cmdResult = runCommand("./projet scenario/t02.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 9 passed " << endl;

    cout << "test 10 starting (./projet scenario/t03.txt --headless)" << endl;
    cmdExpected = "defensor with coordinates 101 117 is not fully within its home: 0";
    cmdResult = runCommand("./projet scenario/t03.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 10 passed " << endl;

    cout << "test 11 starting (./projet scenario/t04.txt --headless)" << endl;
    cmdExpected = "defensor with coordinates 118 102 is not fully within its home: 0";
    cmdResult = runCommand("./projet scenario/t04.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 11 passed " << endl;

    cout << "test 12 starting (./projet scenario/t05.txt --headless)" << endl;
    cmdExpected = "defensor with coordinates 118 117 is not fully within its home: 0";
    cmdResult = runCommand("./projet scenario/t05.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 12 passed " << endl;

    cout << "test 13 starting (./projet scenario/t06.txt --headless)" << endl;
    cmdExpected = "defensor with coordinates 101 102 is not fully within its home: 0";
    cmdResult = runCommand("./projet scenario/t06.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 13 passed " << endl;

    cout << "test 14 starting  (/projet scenario/t07.txt --headless)" << endl;
    cmdExpected = "defensor with coordinates 106 106 overlaps with another exclusive entity at least on 105 105";
    cmdResult = runCommand("./projet scenario/t07.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 14 passed" << endl;

    cout << "test 15 starting (./projet scenario/t08.txt --headless)" << endl;
    cmdExpected = "food with coordinates 78 78 overlaps with another exclusive entity";
    cmdResult = runCommand("./projet scenario/t08.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 15 passed " << endl;

    cout << "test 16 starting (./projet scenario/t09.txt --headless)" << endl;
    cmdExpected = "generator with coordinates 3 3 overlaps with another exclusive entity at least on 4 5";
    cmdResult = runCommand("./projet scenario/t09.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 16 passed " << endl;

    cout << "test 17 starting (./projet scenario/t10.txt --headless)" << endl;
    cmdExpected = "predator with coordinates 22 24 overlaps with another exclusive entity";
    cmdResult = runCommand("./projet scenario/t10.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 17 passed " << endl;

    cout << "test 18 starting (./projet scenario/t11.txt --headless)" << endl;
    cmdExpected = "generator with coordinates 11 5 is not fully within its home: 1";
    cmdResult = runCommand("./projet scenario/t11.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 18 passed " << endl;

    cout << "test 19 starting (./projet scenario/t12.txt --headless)" << endl;
    cmdExpected = "home 0 overlaps with home 1";
    cmdResult = runCommand("./projet scenario/t12.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 19 passed " << endl;

    cout << "test 20 starting (./projet scenario/t13.txt --headless)" << endl;
    cmdExpected = "coordinate 10000000 does not belong to [ 0, 127 ]";
    cmdResult = runCommand("./projet scenario/t13.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 20 passed " << endl;

    cout << "test 21 starting (./projet scenario/t14.txt --headless)" << endl;
    cmdExpected = "combined coordinate 117 and square side 12 do not belong to [ 0, 127 ]";
    cmdResult = runCommand("./projet scenario/t14.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 21 passed " << endl;

    cout << "test 22 starting (./projet scenario/t15.txt --headless)" << endl;
    cmdExpected = "Correct file";
    cmdResult = runCommand("./projet scenario/t15.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 22 passed" << endl;

    cout << "test 23 starting (./projet scenario/t16.txt --headless)" << endl;
    cmdExpected = "Correct file";
    cmdResult = runCommand("./projet scenario/t16.txt --headless");
    assert(stringFuzzyMatch(cmdExpected, cmdResult));
    cout << "test 23 passed" << endl;

    return true;
}

bool stringFuzzyMatch(string str1, string str2)
{
    if(!str1.empty())
    {
        if(str1[str1.length() - 1] == '\n')
        {
            str1.erase(str1.length() - 1);
        }
    }
    if(!str2.empty())
    {
        if(str2[str2.length() - 1] == '\n')
        {
            str2.erase(str2.length() - 1); //efface
        }
    }
    if(not(str2 == str1))
    {
        cout << "Expected :"+str1<<endl;
        cout << "got      :"+str2<<endl;
    }
    return (str2 == str1);
}

string runCommand(const char* command)
{
    string result;
    array<char, 128> outputBuffer;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if(!pipe)
    {
        cout << "command failed" << endl;
        exit(0);
    }
    while(fgets(outputBuffer.data(), outputBuffer.size(), pipe.get()) != nullptr)
    {
        result += outputBuffer.data();
    }
    return result;
}

