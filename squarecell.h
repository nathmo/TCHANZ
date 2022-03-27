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


namespace squarecell
{

    constexpr short unsigned g_dim(7) ;
    constexpr short unsigned g_max(std::pow(2,g_dim)) ;

    class Point {
    private:
        int x=-1;
        int y=-1;
    public:
        Point(int x, int y);
        Point();
        void setCoordX(int xOrigin);
        int getCoordX();
        void setCoordY(int yOrigin);
        int getCoordY();
    };

    class Squarecell {
    private:
        squarecell::Point position;
        int height;
        int width;
        Point cornerBotLeft;
        Point cornerTopRight;
        bool checkHitbox(Point cornerTopRight,Point cornerBotLeft,Point position,int width,int height);
        bool checkPoint(Point point);
        static std::vector<std::vector<bool>> hitBoxGrid ;
    public:
        Squarecell();
        Squarecell(squarecell::Point position, int lenght, int width);
        ~Squarecell();
        Point getPosition();
        void setPosition(Point position);
        int getHeight();
        int getWidth();
        void setHeight(int height);
        void setWidth(int width);
        void setSize(int height, int width);
        Point getHitboxBotLeft();
        Point getHitboxTopRight();
        static int getgMax();
        static int countOverlap(Squarecell hitbox1, Squarecell hitbox2);
        static Point computeHitboxBotLeft(squarecell::Point position, int lenght, int width);
        static Point computeHitboxTopRight(squarecell::Point position, int lenght, int width);
        static void displayRawBoolGrid();
    };

}

#endif //TCHANZ_SQUARECELL_H