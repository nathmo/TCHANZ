/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Interface du module "squarecell"
*/

#ifndef TCHANZ_SQUARECELL_H
#define TCHANZ_SQUARECELL_H

#endif //TCHANZ_SQUARECELL_H
namespace squarecell {
    class Squarecell {
    private:
        int gMax;
        vector <vector<bool>> hitBoxGrid;
        vector <vector<char>> entityGrid;

    public:
        Squarecell(int gmax);

        int getgMax();

        void add(Entity entity);

        void remove(Entity entity);

        bool checkSize(Entity entity);

        bool checkHitbox(Entity entity);

        bool checkHitbox(Entity entity);

        int checkOverlap(Entity entity);
    };

    class Entity {
    private:
        Point position;
        Point size;
        char specie;
    public:
        Entity(Point position, Point size, char specie) {
            this->position = position;
            this->size = size;
            this->specie = specie;
        }

        void setPosition(Point newPosition);

        Point getPosition();

        void setsize(Point sizePosition);

        Point getPosition();

        char getSpecie();

        int checkOverlap(Entity entity);
    };

    class Point {
    private:
        int x;
        int y;
    public:
        Point(x, y) {
            this->x = x;
            this->y = y;
        }

        void setPositionX(xOrigin);

        void getPositionX(xOrigin);

        void setPositionY(yOrigin);

        void getPositionY(yOrigin);
    };
}