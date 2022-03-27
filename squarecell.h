/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Interface du module "squarecell"
*/
#ifndef TCHANZ_SQUARECELL_H
#define TCHANZ_SQUARECELL_H
#include <vector>
#include <math.h>
#include <memory>


namespace squarecell
{
    constexpr short unsigned g_dim(7) ;
    constexpr short unsigned g_max(std::pow(2,g_dim)) ;

    class Point {
    private:
        int x;
        int y;
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
        static std::vector<std::vector<bool>> hitBoxGrid;
        squarecell::Point position;
        int height;
        int width;
        Point cornerBotLeft;
        Point cornerTopRight;
        bool checkHitbox(Point cornerTopRight,Point cornerBotLeft,Point position,int width,int height);
        bool checkPoint(Point point);
    public:
        Squarecell(squarecell::Point position, int lenght, int width);
        ~Squarecell();
        Point getHitboxBotLeft();
        Point getHitboxTopRight();
        static int getgMax();
        static int countOverlap(Squarecell hitbox1, Squarecell hitbox2);
        static Point computeHitboxBotLeft(squarecell::Point position, int lenght, int width);
        static Point computeHitboxTopRight(squarecell::Point position, int lenght, int width);
        static void displayRawBoolGrid();
        static void displayRawEntityGrid();
    };
}

#endif //TCHANZ_SQUARECELL_H