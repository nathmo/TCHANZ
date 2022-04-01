/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Interface du module "squarecell"
*/
#ifndef TCHANZ_SQUARECELL_H
#define TCHANZ_SQUARECELL_H

#include <vector>
#include <cmath>
#include <memory>

namespace squarecell {
    constexpr short unsigned g_dim(7);
    constexpr short unsigned g_max(128);

    class Point {
    private:
        int x=-1;
        int y=-1;
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
        squarecell::Point position;
        int height;
        int width;
        char kind;
        Point cornerBotLeft;
        Point cornerTopRight;
        static std::vector<std::vector<char>> hitBoxGrid ;

    public:
        Squarecell();
        Squarecell(squarecell::Point position, int height, int width, char kind);
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
        static bool checkOverlap(squarecell::Point position, int width, int height, char kindToCheck);
        static std::vector<squarecell::Point> getOverlap(squarecell::Point position, int width,
                                                         int height, char kindToCheck);
        static int countOverlap(squarecell::Point position1, int width1,int height1,
                                        squarecell::Point position2, int width2,int height2);
        static int getgMax();
        static Point computeHitboxBotLeft(squarecell::Point position, int width, int height);
        static Point computeHitboxTopRight(squarecell::Point position, int width, int height);
        static void displayRawBoolGrid();
    };
}

#endif //TCHANZ_SQUARECELL_H