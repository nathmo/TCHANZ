/*!
  \file   squarecell.h
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  prototype du module "squarecell"
*/
#ifndef TCHANZ_SQUARECELL_H
#define TCHANZ_SQUARECELL_H

#include <vector>
#include <cmath>
#include <memory>
#include "constantes.h"

constexpr short unsigned g_dim(7);
constexpr short unsigned g_max(128);

class Point {
private:
    int x=errorCode;
    int y=errorCode;
    bool checkPoint(long int x,long int y);
public:
    Point(int x,int y);
    Point();
    void setCoordX( int xOrigin);
    int getCoordX();
    void setCoordY(int yOrigin);
    int getCoordY();
    static bool checkPoint(Point point);
};

class Squarecell {
private:
    Point position;
    int height;
    int width;
    char kind;
    Point cornerBotLeft;
    Point cornerTopRight;
    static std::vector<std::vector<char>> hitBoxGrid ;

public:
    Squarecell();
    Squarecell(Point position, int height, int width, char kind);
    ~Squarecell();
    Point getPosition();
    void setPosition(Point position);
    int getHeight();
    int getWidth();
    void setHeight(int height);
    void setWidth(int width);
    void setSize(int width,int height);
    Point getHitboxBotLeft();
    Point getHitboxTopRight();
    static bool checkHitbox(Point position, int width, int height);
    static bool checkOverlap(Point position, int width, int height, char kindToCheck);
    static std::vector<Point> getOverlap(Point position, int width,
                                                     int height, char kindToCheck);
    static int countOverlap(Point position1, int width1,int height1,
                                    Point position2, int width2,int height2);
    static int countOverlap(Point cornerBotLeft1, Point cornerTopRight1,
                            Point cornerBotLeft2, Point cornerTopRight2);
    static int getgMax();
    static Point computeHitboxBotLeft(Point position, int width, int height);
    static Point computeHitboxTopRight(Point position, int width, int height);
    static void displayRawBoolGrid();
};
    
#endif //TCHANZ_SQUARECELL_H