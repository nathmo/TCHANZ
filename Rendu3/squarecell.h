/*!
  \file   squarecell.h
  \author Nathann Morand (60%) et Felipe Ramirez (40%)
  \date   MARS 2022
  \brief  prototype du module "squarecell"
*/
#ifndef TCHANZ_SQUARECELL_H
#define TCHANZ_SQUARECELL_H

#include <vector>
#include <cmath>
#include <memory>
#include "constantes.h"

class Point {
private:
    int x = errorCode;
    int y = errorCode;

public:
    Point(int x, int y);
    Point();
    void setCoordX(int xOrigin);
    int getCoordX();
    void setCoordY(int yOrigin);
    int getCoordY();
    static bool isCoordInRange(long int coord);
    static bool checkPoint(Point point);
    static Point checkPoint(long int x, long int y);
    bool operator==(Point point);
    static double distanceAbs(Point start, Point stop);
};

class Squarecell {
private:
    Point position;
    int height;
    int width;
    char kind;
    bool isPositionAtCenter;
    Point cornerBotLeft;
    Point cornerTopRight;
    static std::vector<std::vector<char>> hitBoxGrid ;
    void freeArea();
    void occupyArea();

public:
    Squarecell();
    Squarecell(Point position, int height, int width,
               char kind, bool isPositionAtCenter);
    ~Squarecell();
    Point getPosition();
    void setPosition(Point position);
    int getHeight();
    int getWidth();
    void setHeight(int height);
    void setWidth(int width);
    void setSize(int width, int height);
    Point getHitboxBotLeft();
    Point getHitboxTopRight();
    bool getIsPositionAtCenter();
    //Check that the position + its size still fully fit in the grid
    static bool checkHitbox(Point position, int width,
                            int height, bool isPositionAtCenter);
    static bool ensureFitInGrid(Point position, int width,
                                int height, bool isPositionAtCenter);
    // return true if an shape of the choosen type overlap the given region
    static bool checkOverlap(Point position, int width, int height,
                             char kindToCheck, bool isPositionAtCenter);
    // return the list of overlapping point if an shape of the choosen type overlap
    static std::vector<Point> getOverlap(Point position, int width, int height,
                                         char kindToCheck, bool isPositionAtCenter);
    // return the number of overlapping point between two shape
    static int countOverlap(Point position, int width, int height,
                            char kindToCheck, bool isPositionAtCenter);
    static int countOverlap(Point position1, int width1, int height1,
                            bool isPositionAtCenter1,
                            Point position2, int width2,int height2,
                            bool isPositionAtCenter2);
    static int countOverlap(Point cornerBotLeft1, Point cornerTopRight1,
                            Point cornerBotLeft2, Point cornerTopRight2);
    static std::vector<Point> findFreeInArea(Point cornerBotLeft,Point cornerTopRight,
                                             int width, int height, char filter);
    // return the left bottom corner of the shape
    static Point computeHitboxBotLeft(Point position, int width,
                                      int height, bool isPositionAtCenter);
    // same but for the right top corner of the shape
    static Point computeHitboxTopRight(Point position, int width,
                                       int height, bool isPositionAtCenter);
    // used to display in the the grid
    static void displayRawGrid();
    static void square(int x, int y, int colorCode);
    static void losange(int x, int y, int colorCode);
    static void perimeter(int xBotLeft, int yBotLeft, int sizeSide, int colorCode);
    static void diagonale(int x, int y, int id, int side);
    static void grille(int x, int y, int id, int side);
    static void FullGrid();
};
    
#endif //TCHANZ_SQUARECELL_H