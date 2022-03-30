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
#include "entity.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

vector<vector<char>>  squarecell::Squarecell::hitBoxGrid = vector<vector<char>> (squarecell::g_max,vector<char> (squarecell::g_max));

squarecell::Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
squarecell::Point::Point()
{
    // nothing to do
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
squarecell::Squarecell::Squarecell()
{

}
squarecell::Squarecell::Squarecell(squarecell::Point position, int width,int height, char kind)
{
    this->height = height;
    this->width = width;
    this->position = position;
    this->kind = kind;
    cornerBotLeft = squarecell::Squarecell::computeHitboxBotLeft(position, width, height);
    cornerTopRight = squarecell::Squarecell::computeHitboxTopRight(position, width, height);
    bool isElligible = squarecell::Squarecell::checkHitbox(cornerTopRight, cornerBotLeft, position, width, height)
                       and squarecell::Squarecell::checkPoint(position);
    if(isElligible)
    {
        for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++)
        {
            for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++)
            {
                if(hitBoxGrid[i][j]==emptyCST)
                {
                    hitBoxGrid[i][j] = kind;
                }
                else if(not (hitBoxGrid[i][j] & kind)) // if the entity is not aldready here
                {
                    hitBoxGrid[i][j] = (hitBoxGrid[i][j] ^ kind);
                }
                else
                {
                    cout << "uncatched exception : two entity overlap at "+to_string(i)+", "+to_string(j)<<endl;
                    squarecell::Squarecell::displayRawBoolGrid();
                    exit(0);
                }
            }
        }
    }

}
squarecell::Squarecell::~Squarecell()
{
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++)
    {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++)
        {
            if(hitBoxGrid[i][j] == kind)
            {
                hitBoxGrid[i][j] = emptyCST;
            }
            else if(hitBoxGrid[i][j] == emptyCST)
            {
                cout << "trying to clean the grid from something aldready cleaned !" << endl;
                exit(0);
            }
            else
            {
                hitBoxGrid[i][j] = (hitBoxGrid[i][j] ^ kind);
            }
        }
    }
}

squarecell::Point squarecell::Squarecell::getPosition()
{
    return position;
}
void squarecell::Squarecell::setPosition(squarecell::Point position)
{
    this->position = position;
}
int squarecell::Squarecell::getHeight()
{
    return height;
}
int squarecell::Squarecell::getWidth()
{
    return width;
}
void squarecell::Squarecell::setHeight(int height)
{
    this->height = height;
}
void squarecell::Squarecell::setWidth(int width)
{
    this->width = width;
}
void squarecell::Squarecell::setSize(int width,int height)
{
    this->width = width;
    this->height = height;
}
squarecell::Point squarecell::Squarecell::getHitboxBotLeft()
{
    return cornerBotLeft;
}
squarecell::Point squarecell::Squarecell::getHitboxTopRight()
{
    return cornerTopRight;
}
int squarecell::Squarecell::getgMax()
{
    return g_max;
}

bool squarecell::Squarecell::checkPoint(squarecell::Point point)
{
    bool status = true;
    if(not ((point.getCoordX() >= 0) and (point.getCoordX() < squarecell::g_max))) // not in [0;127]
    {
        error_squarecell::print_index(point.getCoordX(), squarecell::g_max);
        exit(EXIT_FAILURE);
        status = false;
    }
    if(not ((point.getCoordY() >= 0) and (point.getCoordY() < squarecell::g_max))) // not in [0;127]
    {
        error_squarecell::print_index(point.getCoordY(), squarecell::g_max);
        exit(EXIT_FAILURE);
        status = false;
    }
    return status;
}

bool squarecell::Squarecell::checkHitbox(squarecell::Point cornerTopRight, squarecell::Point cornerBotLeft,
                                         squarecell::Point position,int width,int height)
{
    bool status = true;
    vector<int> PointToCheck = {cornerBotLeft.getCoordX(),
                                cornerBotLeft.getCoordY(),
                                cornerTopRight.getCoordX(),
                                cornerTopRight.getCoordY(),};
    for(int i=0;i<4;i++)
    {
        if(not((PointToCheck[i] >= 0) and (PointToCheck[i] < squarecell::g_max))) // not in [0;127]
        {
            if(i%2==0)// check for X coordinate error
            {
                cout << error_squarecell::print_outside(position.getCoordX(),
                                                        width,
                                                        squarecell::g_max) << endl;
                exit(EXIT_FAILURE);
            }
            else if(i%2==1) // check for Y coordinate error
            {
                cout << error_squarecell::print_outside(position.getCoordY(),
                                                        height,
                                                        squarecell::g_max) << endl;
                exit(EXIT_FAILURE);
            }
            status = false;
        }
    }
    if(not((((height % 2) == 0) and ((width % 2) == 0))or(((height % 2) == 1)and((width % 2) == 1))))
    {
        cout << "shape is not a square" << endl;
        status = false;
        exit(EXIT_FAILURE);
    }
    return status; // true if all test pass, false otherwise (and display the set message)
}
bool squarecell::Squarecell::checkOverlap(squarecell::Point position, int width, int height, char kindToCheck)
{
    Point cornerBotLeft = squarecell::Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = squarecell::Squarecell::computeHitboxTopRight(position, width, height);
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++)
    {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++)
        {
            if((hitBoxGrid[i][j] & kindToCheck)) // boolean check that the entity is not present
            {
                return true;
            }
        }
    }
    return false;
}
vector<squarecell::Point> squarecell::Squarecell::getOverlap(squarecell::Point position, int width, int height, char kindToCheck)
{
    Point cornerBotLeft = squarecell::Squarecell::computeHitboxBotLeft(position, width, height);
    Point cornerTopRight = squarecell::Squarecell::computeHitboxTopRight(position, width, height);
    vector<squarecell::Point> collisionList;
    for(int i = cornerBotLeft.getCoordX(); i <= cornerTopRight.getCoordX(); i++)
    {
        for(int j = cornerBotLeft.getCoordY(); j <= cornerTopRight.getCoordY(); j++)
        {
            if((hitBoxGrid[i][j] & kindToCheck)) // boolean check that the entity is not present
            {
                collisionList.push_back(squarecell::Point(i,j));
            }
        }
    }
    return collisionList;
}
int squarecell::Squarecell::countOverlap(squarecell::Squarecell hitbox1, squarecell::Squarecell hitbox2)
{
    int overlappingArea = 0;

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
                if(hitBoxGrid[i][j]==nourritureCST)
                    status = 'N';
                else if(hitBoxGrid[i][j]==fourmilliereCST)
                    status = 'F';
                else if(hitBoxGrid[i][j]==fourmiGeneratorCST)
                    status = 'g';
                else if(hitBoxGrid[i][j]==fourmiCollectorCST)
                    status = 'c';
                else if(hitBoxGrid[i][j]==fourmiPredatorCST)
                    status = 'p';
                else if(hitBoxGrid[i][j]==fourmiDefensorCST)
                    status = 'd';
                else
                    status = 'X';
            }else{
                status = ".";
            }
            lineOfMap = lineOfMap + status + "";
        }
        cout << lineOfMap << endl;
    }
}

squarecell::Point squarecell::Squarecell::computeHitboxBotLeft(squarecell::Point position, int width, int height)
{
    Point botLeft;
    if(width%2==0)
    {
        botLeft.setCoordX(position.getCoordX());
    }
    else if(width%2==1)
    {
        botLeft.setCoordX(position.getCoordX()-(width-1)/2);
    }
    if(height%2==0)
    {
        botLeft.setCoordY(position.getCoordY());
    }
    else if(height%2==1)
    {
        botLeft.setCoordY(position.getCoordY()-(height-1)/2);
    }
    return botLeft;
}

squarecell::Point squarecell::Squarecell::computeHitboxTopRight(squarecell::Point position, int width, int height)
{
    Point topRight;
    if(width%2==0)
    {
        topRight.setCoordX(position.getCoordX()+width);
    }
    else if(width%2==1)
    {
        topRight.setCoordX(position.getCoordX()+(width-1)/2);
    }
    if(height%2==0)
    {
        topRight.setCoordY(position.getCoordY()+height);
    }
    else if(height%2==1)
    {
        topRight.setCoordY(position.getCoordY()+(height-1)/2);
    }
    return topRight;
}
