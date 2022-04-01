/*!
  \file   squarecell.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implémentation du module "squarecell".
*/
#include "squarecell.h"
#include "error_squarecell.h"
#include "constantes.h"
#include "message.h"
#include "entity.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

vector<vector<char>>  Squarecell::hitBoxGrid = vector<vector<char>> (
                                                          g_max,vector<char> (g_max));

Point::Point(int x,int y) {
    if(Point::checkPoint(x,y))
    {
        this->x = x;
        this->y = y;
    }
}

Point::Point() {
    // nothing to do
}

void Point::setCoordX(int xOrigin) {
    x = xOrigin;
}

int Point::getCoordX() {
    return x;
}

void Point::setCoordY(int yOrigin) {
    y = yOrigin;
}

int Point::getCoordY() {
    return y;
}

bool Point::checkPoint(Point point) {
    bool status = true;
    if(not ((point.getCoordX() >= 0) and (point.getCoordX() < g_max))) {// not in [0;127]
        cout << error_squarecell::print_index(point.getCoordX(), g_max);
        exit(EXIT_FAILURE);
        status = false;
    }

    if(not ((point.getCoordY() >= 0) and (point.getCoordY() < g_max))) {// not in [0;127]
        cout << error_squarecell::print_index(point.getCoordY(), g_max);
        exit(EXIT_FAILURE);
        status = false;
    }
    return status;
}
bool Point::checkPoint(long int x,long int y) {
    bool status = true;
    if(not ((x >= 0) and (x < g_max))) { // not in [0;127]
        cout << error_squarecell::print_index(x, g_max-1);
        exit(EXIT_FAILURE);
        status = false;
    }

    if(not ((y >= 0) and (y < g_max))) {// not in [0;127]
        cout << error_squarecell::print_index(y, g_max-1);
        exit(EXIT_FAILURE);
        status = false;
    }
    return status;
}

Squarecell::Squarecell() {
}

Squarecell::Squarecell(Point position, int width,int height, char kind) {
    this->height = height;
    this->width = width;
    this->position = position;
    this->kind = kind;
    cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    bool isElligible = Squarecell::checkHitbox(position,width,height)
                       and Point::checkPoint(position);
    if(isElligible) {
        for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
            for(int j=cornerBotLeft.getCoordY(); j<=cornerTopRight.getCoordY(); j++) {
                if(hitBoxGrid[i][j]==emptyCST) {
                    hitBoxGrid[i][j] = kind;
                } else if(not (hitBoxGrid[i][j] & kind)) { // if the entity is not aldready here
                    hitBoxGrid[i][j] = (hitBoxGrid[i][j] ^ kind);
                } else {
                    cout << "uncatched exception : two entity overlap at "
                            +to_string(i)+", "+to_string(j)<<endl;
                    Squarecell::displayRawBoolGrid();
                    exit(0);
                }
            }
        }
    }

}

Squarecell::~Squarecell() {
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if(hitBoxGrid[i][j] == kind) {
                hitBoxGrid[i][j] = emptyCST;
            } else if(hitBoxGrid[i][j] == emptyCST) {
                cout << "trying to clean the grid from something aldready cleaned !"
                     << endl;
                exit(0);
            } else {
                hitBoxGrid[i][j] = (hitBoxGrid[i][j] ^ kind);
            }
        }
    }
}

Point Squarecell::getPosition() {
    return position;
}

void Squarecell::setPosition(Point position) {
    this->position = position;
}

int Squarecell::getHeight() {
    return height;
}

int Squarecell::getWidth() {
    return width;
}

void Squarecell::setHeight(int height) {
    this->height = height;
}

void Squarecell::setWidth(int width) {
    this->width = width;
}

void Squarecell::setSize(int width,int height) {
    this->width = width;
    this->height = height;
}

Point Squarecell::getHitboxBotLeft() {
    return cornerBotLeft;
}

Point Squarecell::getHitboxTopRight() {
    return cornerTopRight;
}

int Squarecell::getgMax() {
    return g_max;
}

bool Squarecell::checkHitbox(Point position, int width, int height) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    bool status = true;
    vector<int> PointToCheck ={cornerBotLeft.getCoordX(),cornerBotLeft.getCoordY(),
                               cornerTopRight.getCoordX(),cornerTopRight.getCoordY(),};
    for(int i=0;i<4;i++) {
        if(not((PointToCheck[i] >= 0) and (PointToCheck[i] < g_max))) {//not in [0;127]
            if(i%2==0) { // check for X coordinate error
                cout << error_squarecell::print_outside(position.getCoordX(), width,
                                                        g_max-1);
                exit(EXIT_FAILURE);
            } else if(i%2==1) { // check for Y coordinate error 
                cout << error_squarecell::print_outside(position.getCoordY(), height,
                                                        g_max-1);
                exit(EXIT_FAILURE);
            }
            status = false;
        }
    }
    if(not((((height % 2) == 0) and ((width % 2) == 0))or(((height % 2) == 1)and
                                                               ((width % 2) == 1)))) {
        cout << "shape is not a square" << endl;
        status = false;
        exit(EXIT_FAILURE);
    }
    return status; // true if all test pass, false otherwise (and display the set message)
}

bool Squarecell::checkOverlap(Point position, int width, int height,
                                          char kindToCheck) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if((hitBoxGrid[i][j] & kindToCheck)) {// boolean check that the entity is not present
                return true;
            }
        }
    }
    return false;
}

vector<Point> Squarecell::getOverlap(Point position, int width, int height,
                                     char kindToCheck) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    vector<Point> collisionList;
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if((hitBoxGrid[i][j] & kindToCheck)) { // boolean check that the entity is not present
                collisionList.push_back(Point(i,j));
            }
        }
    }
    return collisionList;
}
int Squarecell::countOverlap(Point position1, int width1,int height1,
                             Point position2, int width2,int height2){
    Point cornerBotLeft1 = Squarecell::computeHitboxBotLeft(position1,
                                                            width1,height1);
    Point cornerTopRight1 = Squarecell::computeHitboxTopRight(position1,
                                                              width1, height1);
    Point cornerBotLeft2 = Squarecell::computeHitboxBotLeft(position2,
                                                            width2, height2);
    Point cornerTopRight2 = Squarecell::computeHitboxTopRight(position2,
                                                              width2, height2);
    if((cornerBotLeft2.getCoordX() > cornerTopRight1.getCoordX()) or
                          (cornerBotLeft1.getCoordX() > cornerTopRight2.getCoordX())){
        return 0; // the interval dont overlap
    }
    if((cornerBotLeft2.getCoordY() > cornerTopRight1.getCoordY()) or
                          (cornerBotLeft1.getCoordY() > cornerTopRight2.getCoordY())){
        return 0; // the interval dont overlap (same but for Y coordinate)
    }
    unsigned int overlapWidth = min(cornerTopRight1.getCoordX(),
                                    cornerTopRight2.getCoordX()) -
                                max(cornerBotLeft1.getCoordX(),
                                    cornerBotLeft2.getCoordX());

    unsigned int overlapHeight = min(cornerTopRight1.getCoordY(),
                                     cornerTopRight2.getCoordY()) -
                                 max(cornerBotLeft1.getCoordY(),
                                     cornerBotLeft2.getCoordY());;

    return (overlapWidth+1) * (overlapHeight+1);
}

void Squarecell::displayRawBoolGrid() {
    for(int i=g_max-1;i>=0;i--) {
        string lineOfMap = "";
        for(int j=0;j<g_max;j++) {
            string status = "X";
            if(hitBoxGrid[i][j]) {
                if(hitBoxGrid[i][j]==nourritureCST)
                    status = 'N';
                else if(hitBoxGrid[i][j]==fourmilliereCST)
                    status = 'F';
                else if(hitBoxGrid[i][j]==fourmiGeneratorCST)
                    status = 'g';
                else if(hitBoxGrid[i][j]==fourmiCollectorCST)
                    status = 'c';
                else if(hitBoxGrid[i][j]==fourmiPredatorCST)
                    status = 'p';
                else if(hitBoxGrid[i][j]==fourmiDefensorCST)
                    status = 'd';
                else
                    status = 'X';
            } else {
                status = ".";
            }
            lineOfMap = lineOfMap + status + "";
        }
        cout << lineOfMap << endl;
    }
}

Point Squarecell::computeHitboxBotLeft(Point position, int width, int height) {
    Point botLeft;
    if(width%2==0) {
        botLeft.setCoordX(position.getCoordX());
    } else if(width%2==1) {
        botLeft.setCoordX(position.getCoordX()-(width-1)/2);
    }
    if(height%2==0) {
        botLeft.setCoordY(position.getCoordY());
    } else if(height%2==1) {
        botLeft.setCoordY(position.getCoordY()-(height-1)/2);
    }
    return botLeft;
}

Point Squarecell::computeHitboxTopRight(Point position, int width, int height) {
    Point topRight;
    if(width%2==0) {
        topRight.setCoordX(position.getCoordX()+width-1);
    } else if(width%2==1) {
        topRight.setCoordX(position.getCoordX()+(width-1)/2);
    }
    if(height%2==0) {
        topRight.setCoordY(position.getCoordY()+height-1);
    } else if(height%2==1) {
        topRight.setCoordY(position.getCoordY()+(height-1)/2);
    }
    return topRight;
}
