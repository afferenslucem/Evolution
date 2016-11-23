#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include "SimpleData.h"

using namespace std;



class Creation
{     
private:          
    short int _hp;
    COORD _coord;
    UNI _commandList[64]; //[1; 8] - ходит [9; 16] - хавать 
    UNI _itForCommand;
    Prim** _area;
    int _height;
    int _width;
    int _countOfStep;
    
    bool _IsWall(int X, int Y)
    {
        if(_area[Y][X] == Wall)
            return 1;

            return 0;
    }  
    //.......................................
    void _Step(UNI command)
    {
        switch (command)
        {
        case 0:                          //  1|2|3
            {   
                if(_IsWall(_coord.X - 1, _coord.Y - 1)) {_hp -= WALL_DAMAGE; break;}//  -------
                _coord.X -= 1;           //  8|X|4
                _coord.Y -= 1;  
                //  -------
                break;
            }                            //  7|6|5
        case 1:
            {     
                if(_IsWall(_coord.X, _coord.Y - 1)){_hp -= WALL_DAMAGE; break;}
                _coord.Y -= 1; 
                break;
            }
        case 2:
            {          
                if(_IsWall(_coord.X + 1, _coord.Y - 1)){_hp -= WALL_DAMAGE; break;}
                _coord.X += 1; 
                _coord.Y -= 1; 
                break;
            }
        case 3:
            {   
                if(_IsWall(_coord.X + 1, _coord.Y)){_hp -= WALL_DAMAGE; break;}
                _coord.X += 1; 
                break;
            }
        case 4:                                   
            {    
                if(_IsWall(_coord.X + 1, _coord.Y + 1)){_hp -= WALL_DAMAGE; break;}
                _coord.X += 1; 
                _coord.Y += 1; 
                break;
            }
        case 5:
            {   
                if(_IsWall(_coord.X, _coord.Y + 1)){_hp -= WALL_DAMAGE; break;}
                _coord.Y += 1; 
                break;
            }
        case 6:
            {          
                if(_IsWall(_coord.X - 1, _coord.Y + 1)){_hp -= WALL_DAMAGE; break;}
                _coord.X -= 1; 
                _coord.Y += 1; 
                break;
            }
        case 7:
            {     
                if(_IsWall(_coord.X - 1, _coord.Y)){_hp -= WALL_DAMAGE; break;}
                _coord.X -= 1;
                break;
            }
        default:
            break;
        }

        _hp--;

        if(_area[_coord.Y][_coord.X] == Food)
            _hp += HP_PLUS;

        if(_area[_coord.Y][_coord.X] == Poison)
            _hp -= POISON_DAMAGE;

        _countOfStep++;
    }
    //Prim _See(UNI command)
    //{
    //    switch (command)
    //    {               
    //    case 9:                                                     //  9|10|11
    //        {                                                       //  -------
    //            return _area[_coord.Y - 1][_coord.X - 1];           //  -------
    //        }                                                       // 15|14|13
    //    case 10:
    //        {
    //            return _area[_coord.Y - 1][_coord.X];
    //        }
    //    case 11:
    //        {
    //            return _area[_coord.Y - 1][_coord.X + 1];
    //        }
    //    case 12:
    //        {
    //            return _area[_coord.Y][_coord.X + 1];
    //        }
    //    case 13:
    //        {
    //            return _area[_coord.Y + 1][_coord.X + 1];
    //        }
    //    case 14:
    //        {
    //            return _area[_coord.Y + 1][_coord.X];
    //        }
    //    case 15:
    //        {
    //            return _area[_coord.Y + 1][_coord.X - 1];
    //        }
    //    case 16:
    //        {
    //            return _area[_coord.Y][_coord.X - 1];
    //        }
    //    default:
    //        break;
    //    }
    //}
    void _Mutation()
    {

        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> dist(0, 63);
        uniform_int_distribution<> dist2(1, COUNT_OF_COMMAND);

        _commandList[dist(gen)] = dist2(gen);
    }
    void _Eat(COORD coord)
    {
        if(_area[coord.Y][coord.X] == Poison)
            _hp -= POISON_DAMAGE;

        if(_area[coord.Y][coord.X] == Food)
            _hp += HP_PLUS;

        _area[coord.Y][coord.X] == Void;
    }
    bool _IsAlive()
    {
        if(_hp <= 0)
            return 0;

        return 1;
    }
    
public: 
    void operator = (Creation crt)
    {
        _hp = crt._hp;
        _coord = crt._coord;
        
        for(int i = 0; i < 63; i++)
            _commandList[i] = crt._commandList[i];

        _itForCommand = crt._itForCommand;
        _area = crt._area;
        _height = crt._height;
        _width = crt._width;
        _countOfStep = crt._countOfStep;
    }
    Creation()
    {
        for(int i = 0; i < 64; i++)
          _commandList[i] = 0;

        _countOfStep = 0;
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
                              
        _countOfStep = 0;
    }    
    ~Creation(){}
    void Execute()
    {
        if(_commandList[_itForCommand] > 0 && 9 > _commandList[_itForCommand])
            _Step(_commandList[_itForCommand]);

        _itForCommand = (++_itForCommand + _commandList[_itForCommand]) % 64;
    }
};