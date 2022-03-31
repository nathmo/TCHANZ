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

    public:
        Point(int x,int y);
        Point();
        void setCoordX( int xOrigin);
        int getCoordX();
        void setCoordY(int yOrigin);
        int getCoordY();
    };

    class Squarecell {
    private:
        squarecell::Point position;
        int height;
        int width;
        char kind;
        Point cornerBotLeft;
        Point cornerTopRight;
        bool checkHitbox(Point cornerTopRight,Point cornerBotLeft,Point position,
                         int width,int height);
        bool checkPoint(Point point);
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
        static bool checkOverlap(squarecell::Point position, int width, int height, char kindToCheck);
        static std::vector<squarecell::Point> getOverlap(squarecell::Point position, int width,
                                                         int height, char kindToCheck);
        static int getgMax();
        static int countOverlap(Squarecell hitbox1, Squarecell hitbox2);
        static Point computeHitboxBotLeft(squarecell::Point position, int width, int height);
        static Point computeHitboxTopRight(squarecell::Point position, int width, int height);
        static void displayRawBoolGrid();
    };
}

#endif //TCHANZ_SQUARECELL_H