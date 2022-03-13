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



namespace squarecell {
    constexpr short unsigned g_dim(7) ;
    constexpr short unsigned g_max(std::pow(2,g_dim)) ;

    class Point {
    private:
        int x;
        int y;
    public:
        Point(int x, int y);
        Point();
        void setPositionX(int xOrigin);
        void getPositionX(int xOrigin);
        void setPositionY(int yOrigin);
        void getPositionY(int yOrigin);
    };
    class Entity {
    private:
        Point position;
        Point size;
        char specie;
    public:
        Entity(Point position, Point size, char specie);
        void setPosition(Point newPosition);
        Point getPosition();
        void setsize(Point newSize);
        Point getsize();
        char getSpecie();
        int checkOverlap(Entity entity);
    };
    class Squarecell {
    private:
        std::vector <std::vector<bool>> hitBoxGrid;
        std::vector <std::vector<char>> entityGrid;
    public:
        Squarecell();
        int getgMax();
        void add(Entity entity);
        void remove(Entity entity);
        bool checkSize(Entity entity);
        bool checkHitbox(Entity entity);
        int checkOverlap(Entity entity);
    };
}
#endif //TCHANZ_SQUARECELL_H