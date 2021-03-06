/*!
  \file   squarecell.cc
  \author Nathann Morand (60%) et Felipe Ramirez (40%)
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
#include "graphic.h"

using namespace std;

vector<vector<char>> Squarecell::hitBoxGrid = vector<vector<char>> (g_max,
                                                                vector<char> (g_max));

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point() {}

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

bool Point::isCoordInRange(long int coord) {
    bool status = false;
    if((coord >= 1) and (coord <= (g_max-1))) {
        status = true;
    }
    return status;
}

bool Point::checkPoint(Point point) {
    bool status = true;
    if(not((point.getCoordX() >= 0) and (point.getCoordX() < g_max))) {
        status = false;
    }

    if(not((point.getCoordY() >= 0) and (point.getCoordY() < g_max))) {
        status = false;
    }
    return status;
}

Point Point::checkPoint(long int x, long int y) {
    if(not((x >= 0) and (x < g_max))) { // not in [0;127]
        cout << error_squarecell::print_index(x, g_max-1);
        throw(errorCode);
    }

    if(not((y >= 0) and (y < g_max))) { // not in [0;127]
        cout << error_squarecell::print_index(y, g_max-1);
        throw(errorCode);
    }
    return Point(x, y);
}

bool Point::operator==(Point point) {
    return ((point.x == x) and (point.y == y));
}

double Point::distanceAbs(Point start, Point stop) {
    double xsq = pow((start.getCoordX() - stop.getCoordX()), 2);
    double ysq = pow((start.getCoordY() - stop.getCoordY()), 2);
    return sqrt(xsq + ysq);
}

void Squarecell::freeArea() {
    if((width == 0) or (height == 0)) {
        return;
    }
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

void Squarecell::occupyArea() {
    if((width == 0) or (height == 0)){
        return;
    }
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if(hitBoxGrid[i][j] == emptyCST) { // add the entity the grid
                hitBoxGrid[i][j] = kind;
            } else if(not(hitBoxGrid[i][j] & kind)) { // ensure nothing is there
                hitBoxGrid[i][j] = (hitBoxGrid[i][j] ^ kind);
            } else {                                   // otherwise throw error
                cout << "uncatched exception : two entity overlap at "
                        + to_string(i) + ", " + to_string(j) << endl;
                Squarecell::displayRawGrid();
                exit(0);
            }
        }
    }
}

Squarecell::Squarecell() {}

Squarecell::Squarecell(Point position, int width,int height,
                       char kind, bool isPositionAtCenter) {
    this->height = height;
    this->width = width;
    this->position = position;
    this->kind = kind;
    this->isPositionAtCenter = isPositionAtCenter;
    cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                     isPositionAtCenter);
    cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                       isPositionAtCenter);
    bool isElligible = Squarecell::checkHitbox(position, width, height,
                                               isPositionAtCenter)
                                                      and Point::checkPoint(position);
    if(isElligible) { // if the coordinate fit in the grid
        occupyArea();
    }
}

Squarecell::~Squarecell() {
    freeArea();
}

Point Squarecell::getPosition() {
    return position;
}

void Squarecell::setPosition(Point position) {
    freeArea();
    this->position = position;
    cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                     isPositionAtCenter);
    cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                       isPositionAtCenter);
    bool isElligible = Point::checkPoint(position);
    if(isElligible) { // if the coordinate fit in the grid
        occupyArea();
    }
}

int Squarecell::getHeight() {
    return height;
}

int Squarecell::getWidth() {
    return width;
}

void Squarecell::setHeight(int height) {
    freeArea();
    this->height = height;
    if(height == 0){
        cornerBotLeft = Point();
        cornerTopRight = Point();
        return;
    }
    cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                     isPositionAtCenter);
    cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                       isPositionAtCenter);
    bool isElligible = Point::checkPoint(position);
    if(isElligible) { // if the coordinate fit in the grid
        occupyArea();
    }
}

void Squarecell::setWidth(int width) {
    freeArea();
    this->width = width;
    if(width == 0) {
        cornerBotLeft = Point();
        cornerTopRight = Point();
        return;
    }
    cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                     isPositionAtCenter);
    cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                       isPositionAtCenter);
    bool isElligible = Point::checkPoint(position);
    if(isElligible) { // if the coordinate fit in the grid
        occupyArea();
    }
}

void Squarecell::setSize(int width, int height) {
    freeArea();
    this->width = width;
    this->height = height;
    if((width == 0) or (height == 0)){
        cornerBotLeft = Point();
        cornerTopRight = Point();
        return;
    }
    cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                     isPositionAtCenter);
    cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                       isPositionAtCenter);
    bool isElligible = Point::checkPoint(position);
    if(isElligible) { // if the coordinate fit in the grid
        occupyArea();
    }
}

Point Squarecell::getHitboxBotLeft() {
    return cornerBotLeft;
}

Point Squarecell::getHitboxTopRight() {
    return cornerTopRight;
}

bool Squarecell::getIsPositionAtCenter() {
    return isPositionAtCenter;
}

bool Squarecell::checkHitbox(Point position, int width,
                             int height, bool isPositionAtCenter) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                           isPositionAtCenter);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                             isPositionAtCenter);
    bool status = true;
    vector<int> PointToCheck = {cornerBotLeft.getCoordX(),cornerBotLeft.getCoordY(),
                               cornerTopRight.getCoordX(),cornerTopRight.getCoordY()};
    for(int i(0); i < 4; i++) {
        if(not((PointToCheck[i] >= 0) and (PointToCheck[i] < g_max))) {//not in[0;127]
            if(i%2 == 0) { // check for X coordinate error
                cout << error_squarecell::print_outside(position.getCoordX(), width,
                                                        g_max-1);
                throw(errorCode);
            } else if(i%2 == 1) { // check for Y coordinate error
                cout << error_squarecell::print_outside(position.getCoordY(), height,
                                                        g_max-1);
                throw(errorCode);
            }
            status = false;
        }
    }
    if(not((((height % 2) == 0) and ((width % 2) == 0)) or (((height % 2) == 1) and
                                                               ((width % 2) == 1)))) {
        cout << "shape is not a square" << endl;
        status = false;
        throw(errorCode);
    }
    return status; // true if it fit, false otherwise (and display the set message)
}

bool Squarecell::ensureFitInGrid(Point position, int width,
                                 int height, bool isPositionAtCenter) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                           isPositionAtCenter);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                             isPositionAtCenter);
    bool status = true;
    vector<int> PointToCheck ={cornerBotLeft.getCoordX(),cornerBotLeft.getCoordY(),
                               cornerTopRight.getCoordX(),cornerTopRight.getCoordY()};
    for(int i(0); i < 4; i++) {
        if(not((PointToCheck[i] >= 0) and (PointToCheck[i] < g_max))) {//not in[0;127]
            status = false;
        }
    }
    return status; // true if it fit, false otherwise
}

bool Squarecell::checkOverlap(Point position, int width, int height,
                              char kindToCheck, bool isPositionAtCenter) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                           isPositionAtCenter);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                             isPositionAtCenter);
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
                                     char kindToCheck, bool isPositionAtCenter) {
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                           isPositionAtCenter);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                             isPositionAtCenter);
    vector<Point> collisionList;
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if((hitBoxGrid[i][j] & kindToCheck)) { //check no entity is present there
                collisionList.push_back(Point(i, j)); // add each overlapping point
            }                                        // to a vector
        }
    }
    return collisionList;
}

int Squarecell::countOverlap(Point position, int width, int height,
                             char kindToCheck, bool isPositionAtCenter) {
    int overlap = 0;
    Point cornerBotLeft = Squarecell::computeHitboxBotLeft(position, width, height,
                                                           isPositionAtCenter);
    Point cornerTopRight = Squarecell::computeHitboxTopRight(position, width, height,
                                                             isPositionAtCenter);
    vector<Point> collisionList;
    if(cornerBotLeft.getCoordX() >= g_max){
        cornerBotLeft = Point(127,cornerBotLeft.getCoordY());
    }
    if(cornerBotLeft.getCoordY() >= g_max){
        cornerBotLeft = Point(cornerBotLeft.getCoordX(),127);
    }
    if(cornerBotLeft.getCoordX() < 0){
        cornerBotLeft = Point(0,cornerBotLeft.getCoordY());
    }
    if(cornerBotLeft.getCoordY() < 0){
        cornerBotLeft = Point(cornerBotLeft.getCoordX(),0);
    }
    if(cornerTopRight.getCoordX() >= g_max){
        cornerTopRight = Point(127,cornerTopRight.getCoordY());
    }
    if(cornerTopRight.getCoordY() >= g_max){
        cornerTopRight = Point(cornerTopRight.getCoordX(),127);
    }
    if(cornerTopRight.getCoordX() < 0){
        cornerTopRight = Point(0,cornerTopRight.getCoordY());
    }
    if(cornerTopRight.getCoordY() < 0){
        cornerTopRight = Point(cornerTopRight.getCoordX(),0);
    }
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++) {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++) {
            if((hitBoxGrid[i][j] & kindToCheck)) { //check no entity is present there
                overlap++; // otherwise add it to the count
            }
        }
    }
    return overlap;
}

int Squarecell::countOverlap(Point position1, int width1, int height1,
                             bool isPositionAtCenter1,
                             Point position2, int width2, int height2,
                             bool isPositionAtCenter2) {
    // compute the corner of the rectangle (or square)
    Point cornerBotLeft1 = Squarecell::computeHitboxBotLeft(position1, width1,
                                                        height1, isPositionAtCenter1);
    Point cornerTopRight1 = Squarecell::computeHitboxTopRight(position1, width1,
                                                        height1, isPositionAtCenter1);
    Point cornerBotLeft2 = Squarecell::computeHitboxBotLeft(position2, width2,
                                                        height2, isPositionAtCenter2);
    Point cornerTopRight2 = Squarecell::computeHitboxTopRight(position2, width2,
                                                        height2, isPositionAtCenter2);
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

vector<Point> Squarecell::findFreeInArea(Point cornerBotLeft, Point cornerTopRight,
                                         int width, int height, char filter) {
    vector<Point> space = {};
    int paddingWidth;
    int paddingHeight;
    if(width%2 == 0) {
        paddingWidth = (width/2);
    } else {
        paddingWidth = ((width-1)/2);
    }
    if(height%2 == 0) {
        paddingHeight = (height/2);
    } else {
        paddingHeight = ((height-1)/2);
    }
    int xStart = cornerBotLeft.getCoordX() + paddingWidth;
    int xStop = cornerTopRight.getCoordX() - paddingWidth;
    int yStart = cornerBotLeft.getCoordY() + paddingHeight;
    int yStop = cornerTopRight.getCoordY() - paddingHeight;
    for(int x = xStart; x <= xStop; x++) {
        for(int y = yStart; y <= yStop; y++) {
            if(Squarecell::checkOverlap(Point(x,y), width, height, filter, true)==0) {
                space.push_back(Point(x, y));
            } // convolute the shape to find a spot where it fit
        }
    }
    return space;
}

Point Squarecell::computeHitboxBotLeft(Point position, int width,
                                       int height, bool isPositionAtCenter) {
    Point botLeft;
    if(not isPositionAtCenter) {
        botLeft.setCoordX(position.getCoordX());
    } else {
        botLeft.setCoordX(position.getCoordX() - (width-1)/2);
    }
    if(not isPositionAtCenter) {
        botLeft.setCoordY(position.getCoordY());
    } else {
        botLeft.setCoordY(position.getCoordY() - (height-1)/2);
    }
    return botLeft;
}

Point Squarecell::computeHitboxTopRight(Point position, int width,
                                        int height, bool isPositionAtCenter) {
    Point topRight;
    if(not isPositionAtCenter) {
        topRight.setCoordX(position.getCoordX() + width - 1);
    } else {
        topRight.setCoordX(position.getCoordX() + (width-1)/2);
    }
    if(not isPositionAtCenter) {
        topRight.setCoordY(position.getCoordY() + height - 1);
    } else if(height%2 == 1) {
        topRight.setCoordY(position.getCoordY() + (height-1)/2);
    }
    return topRight;
}

void Squarecell::displayRawGrid() {
    for(int i = g_max-1; i >= 0; i--) {
        string lineOfMap = "";
        for(int j(0); j < g_max; j++) {
            string status = "X";
            if(hitBoxGrid[i][j]) {
                switch (hitBoxGrid[i][j]) {
                    case nourritureCST:
                        status = 'N';
                        break;
                    case fourmilliereCST:
                        status = 'F';
                        break;
                    case fourmiGeneratorCST:
                        status = 'g';
                        break;
                    case fourmiCollectorCST:
                        status = 'c';
                        break;
                    case fourmiPredatorCST:
                        status = 'p';
                        break;
                    case fourmiDefensorCST:
                        status = 'd';
                        break;
                    default:
                        status = 'X';
                        break;
                }
            } else {
                status = ".";
            }
            lineOfMap = lineOfMap + status + "";
        }
        cout << lineOfMap << endl;
    }
}


void Squarecell::square(int x, int y, int colorCode) {
    vector<vector<double>> linesToDraw;
    double largeur = 1;
    double xCoord = (double)x;
    double yCoord = (double)y;
    double color = colorCode;
    linesToDraw.push_back({xCoord, yCoord+0.5, xCoord+1, yCoord+0.5, largeur, color});

    for(auto command:linesToDraw) {
        Graphic::drawLine(command[0], command[1], command[2],
                          command[3], command[4], command[5]);
    }
}

void Squarecell::losange(int x, int y, int colorCode) {
    vector<vector<double>> linesToDraw;
    float sinBias = 0.27;
    float largeur = 0.72;

    linesToDraw.push_back({x+sinBias, y+sinBias,
                           x+1-sinBias, y+1-sinBias, largeur, 12});

    for(auto command:linesToDraw) {
        Graphic::drawLine(command[0], command[1], command[2],
                          command[3], command[4], command[5]);
    }
}

void Squarecell::perimeter(int xBotLeft, int yBotLeft,  int sizeSide, int colorCode) {
    vector<vector<double>> linesToDraw;
    double color = (double)colorCode;
    //ligne horizontal down
    linesToDraw.push_back({xBotLeft+0.5, yBotLeft+0.5, xBotLeft+sizeSide-0.5,
                           yBotLeft+0.5, 0.3, color});
    //ligne vertical down
    linesToDraw.push_back({xBotLeft+0.5, yBotLeft+0.5, xBotLeft+0.5,
                           yBotLeft+sizeSide-0.5, 0.3, color});
    //ligne verticale depuis le haut
    linesToDraw.push_back({xBotLeft+sizeSide-0.5, yBotLeft+sizeSide-0.5,
                           xBotLeft+sizeSide-0.5, yBotLeft+0.5, 0.3, color});
    //ligne horizontal depuis le haut
    linesToDraw.push_back({xBotLeft+sizeSide-0.5, yBotLeft+sizeSide-0.5,
                           xBotLeft+0.5, yBotLeft+sizeSide-0.5, 0.3, color});
    for(auto command:linesToDraw) {
        Graphic::drawLine(command[0], command[1], command[2],
                          command[3], command[4], command[5]);
    }
}

void Squarecell::diagonale(int x, int y, int id, int side) {//fonction draw Collector
    int lightColor = id + 6;
    int colorCode = id; //on commence en bas a gauche donc foncé au debut
    // int xBotLeft, int yBotLeft,  int sizeSide, int colorCode
    for(int i(0); i < side; i++) {
        for(int j(0); j < side; j++) {
            Squarecell::square(x + j, y + i, colorCode);
            if(colorCode == id) {
                colorCode = lightColor;
            } else {
                colorCode = id;
            }
        }
    }
}

void Squarecell::grille(int x, int y, int id, int side) { //fonction draw Defensor
    int lightColor = id + 6;
    int colorCode = lightColor; //on commence en bas a gauche

    for(int i(0); i < side; i++) {
        for(int j(0); j < side; j++) {
            Squarecell::square(x + j, y + i, colorCode);
            if(colorCode == id) {
                colorCode = lightColor;
            } else {
                colorCode = id;
            }
        }
    }
    Squarecell::square(x + 1, y + 1, id);;//change color center to dark
}

void Squarecell::FullGrid() {
    vector<vector<double>> commandList;
    // white border
    commandList.push_back({0, g_max/2, g_max, g_max/2, g_max, 12});
    // black background
    commandList.push_back({1, g_max/2, g_max-1, g_max/2, g_max-2, 14});
    // vertical line
    for(double x(0); x < g_max+1; x++) {
        commandList.push_back({x, 0, x, g_max, 0.1, 13});
    }
    // horizonal line
    for(double y(0); y < g_max+1; y++) {
        commandList.push_back({0, y, g_max, y, 0.1, 13});
    }
    for(auto command:commandList) {
        Graphic::drawLine(command[0], command[1], command[2],
                          command[3], command[4], command[5]);
    }
}