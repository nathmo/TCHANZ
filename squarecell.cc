/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module "squarecell".
*/

#include "squarecell.h"
#include "error_squarecell.h"
#include "constantes.h"
#include "message.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>


using namespace std;
squarecell::Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
squarecell::Point::Point::Point()
{
    this->x = -1;
    this->y = -1;
}
void squarecell::Point::setCoordX(int xOrigin)
{
    x = xOrigin;
}
int squarecell::Point::getCoordX()
{
    return x;
}
void squarecell::Point::setCoordY(int yOrigin)
{
    y = yOrigin;
}
int squarecell::Point::getCoordY()
{
    return y;
}

squarecell::Entity::Entity(Point position, Point size, char specie)
{
    this->position = position;
    this->size = size;
    this->specie = specie;
}
void squarecell::Entity::setPosition(Point newPosition)
{
    position = newPosition;
}
squarecell::Point squarecell::Entity::getPosition()
{
    return position;
}
void squarecell::Entity::setsize(Point newSize)
{
    size = newSize;
}
squarecell::Point squarecell::Entity::getsize()
{
    return size;
}
char squarecell::Entity::getSpecie()
{
    return specie;
}
int squarecell::Entity::checkOverlap(Entity entity)
{
    // remove if not used
    return 0;
}
int squarecell::Entity::getId()
{
    return id;
}
void squarecell::Entity::setId(int id)
{
    this->id = id;
}

squarecell::Squarecell::Squarecell()
{
    hitBoxGrid = vector<vector<bool>> (g_max, vector<bool>(g_max,false));
    entityGrid = vector<vector<char>> (g_max, vector<char>(g_max, 'E'));
}
int squarecell::Squarecell::getgMax()
{
    return g_max;
}

bool squarecell::Squarecell::add(shared_ptr<Entity> entity)
{
    bool isEligible = squarecell::Squarecell::checkSize(entity)
                and squarecell::Squarecell::checkHitbox(entity)
                and squarecell::Squarecell::checkOverlap(entity);
    if(isEligible)
    {
        if(not((*entity).getSpecie()==fourmilliereCST))
        {
            (*entity).setId(entityList.size());
            entityList.push_back(entity);
            Point hitboxBotLeft = squarecell::getHitboxBotLeft(entity);
            Point hitboxTopRight = squarecell::getHitboxTopRight(entity);
            for(int i = hitboxBotLeft.getCoordX(); i <= hitboxTopRight.getCoordX(); i++)
            {
                for(int j = hitboxBotLeft.getCoordY(); j <= hitboxTopRight.getCoordY(); j++)
                {
                    hitBoxGrid[i][j] = true;
                    entityGrid[i][j] = (*entity).getSpecie();
                }
            }
        }
    }
    return isEligible;
}
bool squarecell::Squarecell::remove(shared_ptr<squarecell::Entity>  entity)
{
    entityList.erase(entityList.begin() + (*entity).getId());//assume only one copy at position
    Point hitboxBotLeft = squarecell::getHitboxBotLeft(entity);
    Point hitboxTopRight = squarecell::getHitboxTopRight(entity);
    for(int i =hitboxBotLeft.getCoordX();i<=hitboxTopRight.getCoordX();i++)
    {
        for(int j =hitboxBotLeft.getCoordY();j<=hitboxTopRight.getCoordY();j++)
        {
            hitBoxGrid[i][j]=false;
            entityGrid[i][j]='E';
        }
    }
    return true;
}

bool squarecell::Squarecell::checkSize(shared_ptr<squarecell::Entity> entity)
{
    bool status = true;
    if(not(((*entity).getPosition().getCoordX() >= 0)
    and    ((*entity).getPosition().getCoordX() < squarecell::g_max)))
    {
        cout << error_squarecell::print_index((*entity).getPosition().getCoordX(), squarecell::g_max)<<endl;
        status = false;
    }
    if(not(((*entity).getPosition().getCoordY() >= 0)
    and    ((*entity).getPosition().getCoordY() < squarecell::g_max)))
    {
        cout << error_squarecell::print_index((*entity).getPosition().getCoordY(), squarecell::g_max)<<endl;
        status = false;
    }
    return status; // true if all test pass, false otherwise (and display the set message)
}

bool squarecell::Squarecell::checkHitbox(shared_ptr<squarecell::Entity> entity)
{
    bool status = true;
    Point hitboxBotLeft = squarecell::getHitboxBotLeft(entity);
    Point hitboxTopRight = squarecell::getHitboxTopRight(entity);
    vector<int> PointToCheck = {hitboxBotLeft.getCoordX(),
                                hitboxBotLeft.getCoordY(),
                                hitboxTopRight.getCoordX(),
                                hitboxTopRight.getCoordY(),};
    for(int i=0;i<4;i++)
    {
        if(not((PointToCheck[i] >= 0)
        and    (PointToCheck[i] < squarecell::g_max)))
        {
            if(i%2==0)// X coordinate error
            {
                cout << error_squarecell::print_outside((*entity).getPosition().getCoordX(),
                                                        (*entity).getsize().getCoordX(),
                                                squarecell::g_max) << endl;
            }
            else if(i%2==1) // Y coordinate error
            {
                cout << error_squarecell::print_outside((*entity).getPosition().getCoordY(),
                                                        (*entity).getsize().getCoordY(),
                                                squarecell::g_max) << endl;
            }
            status = false;
        }
    }
    if(not(((((*entity).getsize().getCoordX() % 2) == 0)
    and     (((*entity).getsize().getCoordY() % 2) == 0))
    or     ((((*entity).getsize().getCoordX() % 2) == 1)
    and     (((*entity).getsize().getCoordY() % 2) == 1))))
    {
        cout << "shape is not a square" << endl;
        status = false;
        exit(0);
    }
    return status; // true if all test pass, false otherwise (and display the set message)
}

bool squarecell::Squarecell::checkOverlap(shared_ptr<squarecell::Entity> entity)
{
    bool noOverlap = true;
    if(squarecell::Squarecell::countOverlap(entity) !=0)
    {
        noOverlap = false;
        if((*entity).getSpecie()==nourritureCST)
        {
            cout << message::food_overlap((*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY()) << endl;
        }
        if((*entity).getSpecie()==fourmilliereCST)
        {
            cout << message::homes_overlap((*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY()) << endl;
        }
        if((*entity).getSpecie()==fourmiGeneratorCST)
        {
            cout << message::generator_overlap((*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY(), (*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY()) << endl;
        }
        if((*entity).getSpecie()==fourmiCollectorCST)
        {
            cout << message::collector_overlap((*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY(), (*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY()) << endl;
        }
        if((*entity).getSpecie()==fourmiDefensorCST)
        {
            cout << message::defensor_overlap((*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY(), (*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY()) << endl;
        }
        if((*entity).getSpecie()==fourmiPredatorCST)
        {
            cout << message::predator_overlap((*entity).getPosition().getCoordX(),(*entity).getPosition().getCoordY()) << endl;
        }
    }
    return noOverlap;
}

int squarecell::Squarecell::countOverlap(shared_ptr<squarecell::Entity> entity)
{
    int overlappingArea = 0;
    Point hitboxBotLeft = squarecell::getHitboxBotLeft(entity);
    Point hitboxTopRight = squarecell::getHitboxTopRight(entity);
    for(int i=hitboxBotLeft.getCoordX();i<=hitboxTopRight.getCoordX();i++)
    {
        for(int j=hitboxBotLeft.getCoordY();i<=hitboxTopRight.getCoordY();i++)
        {
            if(hitBoxGrid[i][j]==true)
            {
                overlappingArea++;
            }
        }
    }
    return overlappingArea;
}

void squarecell::Squarecell::displayRawBoolGrid()
{
    for(int i=g_max-1;i>=0;i--)
    {
        string lineOfMap = "";
        for(int j=0;j<g_max;j++)
        {
            string status = "X";
            if(hitBoxGrid[i][j])
            {
                status = "1";
            }else{
                status = ".";
            }
            lineOfMap = lineOfMap + status + "";
        }
        cout << lineOfMap << endl;
    }
}

void squarecell::Squarecell::displayRawEntityGrid()
{
    for(int i=g_max-1;i>=0;i--)
    {
        string lineOfMap = "";
        for(int j=0;j<g_max;j++)
        {
            string status = "X";
            if(entityGrid[i][j]=='E')
            {
                status = ".";
            }else{
                status = entityGrid[i][j];
            }
            lineOfMap = lineOfMap + status + "";
        }
        cout << lineOfMap << endl;
    }
}
squarecell::Point squarecell::getHitboxBotLeft(shared_ptr<squarecell::Entity> entity)
{
    Point botLeft;
    if((*entity).getsize().getCoordX()%2==0)
    {
        botLeft.setCoordX((*entity).getPosition().getCoordX());
    }
    else if((*entity).getsize().getCoordX()%2==1)
    {
        botLeft.setCoordX((*entity).getPosition().getCoordX()-((*entity).getsize().getCoordX()-1)/2);
    }
    if((*entity).getsize().getCoordY()%2==0)
    {
        botLeft.setCoordY((*entity).getPosition().getCoordY());
    }
    else if((*entity).getsize().getCoordY()%2==1)
    {
        botLeft.setCoordY((*entity).getPosition().getCoordY()-((*entity).getsize().getCoordY()-1)/2);
    }
    return botLeft;
}

squarecell::Point squarecell::getHitboxTopRight(shared_ptr<squarecell::Entity> entity)
{
    Point topRight;
    if((*entity).getsize().getCoordX()%2==0)
    {
        topRight.setCoordX((*entity).getPosition().getCoordX()+(*entity).getsize().getCoordX());
    }
    else if((*entity).getsize().getCoordX()%2==1)
    {
        topRight.setCoordX((*entity).getPosition().getCoordX()+((*entity).getsize().getCoordX()-1)/2);
    }
    if((*entity).getsize().getCoordY()%2==0)
    {
        topRight.setCoordY((*entity).getPosition().getCoordY()+(*entity).getsize().getCoordY());
    }
    else if((*entity).getsize().getCoordY()%2==1)
    {
        topRight.setCoordY((*entity).getPosition().getCoordY()+((*entity).getsize().getCoordY()-1)/2);
    }
    return topRight;
}
