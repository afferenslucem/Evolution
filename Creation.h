#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include "SimpleData.h"

using namespace std;

#define UNI unsigned short int
#define COUNT_OF_COMMAND 20

class Creation
{
private:
    UNI _hp;
    COORD _coord;
    UNI _commandList[64];
    UNI _itForCommand;
    Prim** _area;
    int _height;
    int _width;

    void _Step(UNI command)
    {
        switch (command)
        {
        case 1:                          //  1|2|3
            {                            //  -------
                _coord.X -= 1;           //  8|X|4
                _coord.Y -= 1;           //  -------
                break;
            }                            //  7|6|5
        case 2:
            {          
                _coord.Y -= 1; 
                break;
            }
        case 3:
            {          
                _coord.X += 1; 
                _coord.Y -= 1; 
                break;
            }
        case 4:
            {          
                _coord.X += 1; 
                break;
            }
        case 5:
            {          
                _coord.X += 1; 
                _coord.Y += 1; 
                break;
            }
        case 6:
            {          
                _coord.Y += 1; 
                break;
            }
        case 7:
            {          
                _coord.X -= 1; 
                _coord.Y += 1; 
                break;
            }
        case 8:
            {          
                _coord.X -= 1;
                break;
            }
        default:
            break;
        }
    }
    Prim _See(UNI command)
    {
        switch (command)
        {               
        case 9:                                                     //  9|10|11
            {                                                       //  -------
                return _area[_coord.Y - 1][_coord.X - 1];           //  -------
            }                                                       // 15|14|13
        case 10:
            {
                return _area[_coord.Y - 1][_coord.X];
            }
        case 11:
            {
                return _area[_coord.Y - 1][_coord.X + 1];
            }
        case 12:
            {
                return _area[_coord.Y][_coord.X + 1];
            }
        case 13:
            {
                return _area[_coord.Y + 1][_coord.X + 1];
            }
        case 14:
            {
                return _area[_coord.Y + 1][_coord.X];
            }
        case 15:
            {
                return _area[_coord.Y + 1][_coord.X - 1];
            }
        case 16:
            {
                return _area[_coord.Y][_coord.X - 1];
            }
        default:
            break;
        }
    }
    public:
    void _Mutation()
    {
        int len = 0;
        
        for(int i = 0; i < 63 && _commandList[i + 1]; i++)
            len++;

        
        if(len < 63) len++;

        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> dist(0, len);
        uniform_int_distribution<> dist2(1, COUNT_OF_COMMAND);

        _commandList[dist(gen)] = dist2(gen);
    }

    Creation()
    {
        for(int i = 0; i < 64; i++)
          _commandList[i] = 0;
    }
    Creation(COORD& coord, vector<UNI>& commands, Prim** area, int h, int w)
    {
        this->_hp = 10;
        this->_coord = coord;
        
        for(int i = 0; i < 64; i++)
          _commandList[i] = 0;

        for(int i = 0; i < commands.size(); i++)
            _commandList[i] = commands[i];

        _area = area;

        _height = h;

        _width = w;
    }
    UNI* fd()
    {
        return _commandList;
    }
};