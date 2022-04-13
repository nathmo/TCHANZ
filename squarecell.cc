/*!
  \file   squarecell.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implémentation du module "squarecell".
*/
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include "squarecell.h"
#include "error_squarecell.h"
#include "constantes.h"
#include "message.h"
#include "entity.h"

using namespace std;

vector<vector<char>> Squarecell::hitBoxGrid = vector<vector<char>> (g_max,
                                                                vector<char> (g_max));

Point::Point(int x,int y) {
    if(Point::checkPoint(x,y)) {
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
    if(not ((point.getCoordX() >= 0) and (point.getCoordX() < g_max))) {
        cout << error_squarecell::print_index(point.getCoordX(), g_max);
        throw (-1);
        status = false;
    }

    if(not ((point.getCoordY() >= 0) and (point.getCoordY() < g_max))) {
        cout << error_squarecell::print_index(point.getCoordY(), g_max);
        throw (-1);
        status = false;
    }
    return status;
}
bool Point::checkPoint(long int x,long int y) {
    bool status = true;
    if(not ((x >= 0) and (x < g_max))) { // not in [0;127]
        cout << error_squarecell::print_index(x, g_max-1);
        throw (-1);
        status = false;
    }

    if(not ((y >= 0) and (y < g_max))) {// not in [0;127]
        cout << error_squarecell::print_index(y, g_max-1);
        throw (-1);
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
    if(isElligible) { // if the coordinate fit in the grid
        for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
            for(int j=cornerBotLeft.getCoordY(); j<=cornerTopRight.getCoordY(); j++) {
                if(hitBoxGrid[i][j]==emptyCST) { // add the entity the grid
                    hitBoxGrid[i][j] = kind;
                } else if(not (hitBoxGrid[i][j] & kind)) { // ensure nothing is there
                    hitBoxGrid[i][j] = (hitBoxGrid[i][j] ^ kind);
                } else {                                   // otherwise throw error
                    cout << "uncatched exception : two entity overlap at "
                            +to_string(i)+", "+to_string(j)<<endl;
                    Squarecell::displayRawGrid();
                    exit(0);
                }
            }
        }
    }
}

Squarecell::~Squarecell() {
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if(hitBoxGrid[i][j] == kind) { // clear the grid
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

bool Squarecell::checkHitbox(Point position, int width, int height) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    bool status = true;
    vector<int> PointToCheck ={cornerBotLeft.getCoordX(),cornerBotLeft.getCoordY(),
                               cornerTopRight.getCoordX(),cornerTopRight.getCoordY()};
    for(int i=0;i<4;i++) {
        if(not((PointToCheck[i] >= 0) and (PointToCheck[i] < g_max))) {//not in[0;127]
            if(i%2==0) { // check for X coordinate error
                cout << error_squarecell::print_outside(position.getCoordX(), width,
                                                        g_max-1);
                throw (-1);
            } else if(i%2==1) { // check for Y coordinate error 
                cout << error_squarecell::print_outside(position.getCoordY(), height,
                                                        g_max-1);
                throw (-1);
            }
            status = false;
        }
    }
    if(not((((height % 2) == 0) and ((width % 2) == 0))or(((height % 2) == 1)and
                                                               ((width % 2) == 1)))) {
        cout << "shape is not a square" << endl;
        status = false;
        throw (-1);
    }
    return status; // true if it fit, false otherwise (and display the set message)
}

bool Squarecell::checkOverlap(Point position, int width, int height,
                              char kindToCheck) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if((hitBoxGrid[i][j] & kindToCheck)) {
                return true;                      // return true if the entity collide
            }
        }
    }
    return false; // false if it does not collide
}

vector<Point> Squarecell::getOverlap(Point position, int width, int height,
                                     char kindToCheck) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height);
    vector<Point> collisionList;
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if((hitBoxGrid[i][j] & kindToCheck)) { //check no entity is present there
                collisionList.push_back(Point(i,j)); // add each overlapping point
            }                                        // to a vector
        }
    }
    return collisionList;
}

int Squarecell::countOverlap(Point position1, int width1,int height1,
                             Point position2, int width2,int height2){
    // compute the corner of the rectangle (or square)
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
    } // compute the intervall start and stop
    unsigned int overlapWidth = min(cornerTopRight1.getCoordX(),
                                    cornerTopRight2.getCoordX()) -
                                max(cornerBotLeft1.getCoordX(),
                                    cornerBotLeft2.getCoordX());
    unsigned int overlapHeight = min(cornerTopRight1.getCoordY(),
                                     cornerTopRight2.getCoordY()) -
                                 max(cornerBotLeft1.getCoordY(),
                                     cornerBotLeft2.getCoordY());
    return (overlapWidth+1) * (overlapHeight+1);
}

int Squarecell::countOverlap(Point cornerBotLeft1, Point cornerTopRight1,
                             Point cornerBotLeft2, Point cornerTopRight2) {
    if((cornerBotLeft2.getCoordX() > cornerTopRight1.getCoordX()) or
       (cornerBotLeft1.getCoordX() > cornerTopRight2.getCoordX())) {
        return 0; // the interval dont overlap
    }
    if((cornerBotLeft2.getCoordY() > cornerTopRight1.getCoordY()) or
       (cornerBotLeft1.getCoordY() > cornerTopRight2.getCoordY())) {
        return 0; // the interval dont overlap (same but for Y coordinate)
    }
    unsigned int overlapWidth = min(cornerTopRight1.getCoordX(),
                                    cornerTopRight2.getCoordX()) -
                                max(cornerBotLeft1.getCoordX(),
                                    cornerBotLeft2.getCoordX());
    unsigned int overlapHeight = min(cornerTopRight1.getCoordY(),
                                     cornerTopRight2.getCoordY()) -
                                 max(cornerBotLeft1.getCoordY(),
                                     cornerBotLeft2.getCoordY());
    return (overlapWidth+1) * (overlapHeight+1);
}

void Squarecell::displayRawGrid() {
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

vector<vector<double>> Squarecell::square(int x, int y, int colorCode) {
    vector<vector<double>> linesToDraw;
    double largeur = 1;
    double xCoord = (double)x;
    double yCoord = (double)y;
    double color = colorCode;
    linesToDraw.push_back({xCoord, yCoord+0.5, xCoord+1, yCoord+0.5, largeur, color});

    return linesToDraw;
}

vector<vector<double>> Squarecell::perimeter(int xBotLeft, int yBotLeft,
                                             int sizeSide, int colorCode) {
    vector<vector<double>> linesToDraw;
    double color = (double)colorCode;
    linesToDraw.push_back({xBotLeft+0.5, yBotLeft+0.5, xBotLeft+sizeSide-0.5,
                           yBotLeft+0.5, 0.3, color}); //ligne horizontal
    linesToDraw.push_back({xBotLeft+0.5, yBotLeft+0.5, xBotLeft+0.5,
                           yBotLeft+sizeSide-0.5, 0.3, color}); //ligne vertical en bas gauche
    linesToDraw.push_back({xBotLeft+sizeSide-0.5, yBotLeft+sizeSide-0.5,
                           xBotLeft+sizeSide-0.5, yBotLeft+0.5, 0.3, color}); //ligne verticale depuis le haut
    linesToDraw.push_back({xBotLeft+sizeSide-0.5, yBotLeft+sizeSide-0.5,
                           xBotLeft+0.5, yBotLeft+sizeSide-0.5, 0.3, color}); //ligne horizontal depuis le haut

    return linesToDraw;
}

vector<vector<double>> Squarecell::losange(int x, int y, int colorCode) {
    vector<vector<double>> linesToDraw;
    float sinBias = 0.27;
    float largeur = 0.72;

    linesToDraw.push_back({x+sinBias, y+sinBias, x+1-sinBias, y+1-sinBias,
                           largeur, 12});

    return linesToDraw;
}

vector<vector<double>> Squarecell::FullGrid() {
    vector<vector<double>> commandList;
    //white border
    //xStart, yStart, xStop, yStop, largeur, colorCode
    commandList.push_back({0, g_max/2, g_max, g_max/2, g_max+1, 12});
    // black bacground
    commandList.push_back({1, g_max/2, g_max-1, g_max/2, g_max-2, 14});
    // vertical line
    for(double x=0;x<g_max+1;x++) {
        commandList.push_back({x, 0, x, g_max, 0.1, 13});
    }
    // horizonal line
    for(double y=0;y<g_max+1;y++) {
        commandList.push_back({0, y, g_max, y, 0.1, 13});
    }
    return commandList;
}