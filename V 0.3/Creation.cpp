#pragma once
#include "Creation.h"   


//void Creation::operator = (Creation& crt)
//    {
//        _head = crt._head;
//        _hp = crt._hp;
//        _coord = crt._coord;
//        
//        std::vector<UNI>::iterator first = crt._commandList.begin(), last = crt._commandList.begin();
//        
//        advance(last, 63);
//
//        copy(first, last, back_inserter(_commandList));
//
//        _itForCommand = crt._itForCommand;
//        _area = crt._area;
//        _height = crt._height;
//        _width = crt._width;
//        _countOfStep = crt._countOfStep;
//        _eatingFood = crt._eatingFood;
//        _eatingPoison = crt._eatingPoison;
//    }
Creation::Creation()
    {
        _head = up;

        for(int i = 0; i < 64; i++)
          _commandList[i] = 0;

        _countOfStep = 0;
    }
Creation::Creation(COORD& coord, vector<UNI>& commands, Prim** area, int h, int w)
    {
        _head = up;

        this->_hp = 10;
        this->_coord = coord;

        std::vector<UNI>::iterator first = commands.begin(), last = commands.begin();
        
        advance(last, commands.size() - 1);

        copy(first, last, back_inserter(_commandList));

        for(int i = _commandList.size(); i < 64; i++)
            _commandList.push_back(0);

        _area = area;

        _height = h;

        _width = w;
                              
        _countOfStep = 0;
    }    
Creation::~Creation(){}
void Creation::Execute()
    {
        if(_commandList[_itForCommand] > 0 && 9 > _commandList[_itForCommand])
            _Step(_commandList[_itForCommand]);

        _itForCommand = (++_itForCommand + _commandList[_itForCommand]) % 64;
    }             
void Creation::_Step(UNI command)
    {

        command = (command + _head + 7) % 8;

        switch (command)
        {
        case 0:                          //  1|2|3
            {   
                if(_IsClose(_coord.X - 1, _coord.Y - 1)) {_hp -= WALL_DAMAGE; break;}//  -------
                _coord.X -= 1;           //  8|X|4
                _coord.Y -= 1;  
                //  -------
                break;
            }                            //  7|6|5
        case 1:
            {     
                if(_IsClose(_coord.X, _coord.Y - 1)){_hp -= WALL_DAMAGE; break;}
                _coord.Y -= 1; 
                break;
            }
        case 2:
            {          
                if(_IsClose(_coord.X + 1, _coord.Y - 1)){_hp -= WALL_DAMAGE; break;}
                _coord.X += 1; 
                _coord.Y -= 1; 
                break;
            }
        case 3:
            {   
                if(_IsClose(_coord.X + 1, _coord.Y)){_hp -= WALL_DAMAGE; break;}
                _coord.X += 1; 
                break;
            }
        case 4:                                   
            {    
                if(_IsClose(_coord.X + 1, _coord.Y + 1)){_hp -= WALL_DAMAGE; break;}
                _coord.X += 1; 
                _coord.Y += 1; 
                break;
            }
        case 5:
            {   
                if(_IsClose(_coord.X, _coord.Y + 1)){_hp -= WALL_DAMAGE; break;}
                _coord.Y += 1; 
                break;
            }
        case 6:
            {          
                if(_IsClose(_coord.X - 1, _coord.Y + 1)){_hp -= WALL_DAMAGE; break;}
                _coord.X -= 1; 
                _coord.Y += 1; 
                break;
            }
        case 7:
            {     
                if(_IsClose(_coord.X - 1, _coord.Y)){_hp -= WALL_DAMAGE; break;}
                _coord.X -= 1;
                break;
            }
        default:
            break;
        }

        _hp--;

        if(_area[_coord.Y][_coord.X] == Food)
        {
            _hp += HP_PLUS;
            _eatingFood();
        }

        if(_area[_coord.Y][_coord.X] == Poison)
        {
            _hp -= POISON_DAMAGE;
            _eatingPoison();
        }
       

        _countOfStep++;
    }
void Creation::_See(UNI command)
    {

        command = (command + _head + 7) % 8;

        switch (command)
        {               
        case 9:                                                     //  9|10|11
            {                                                       //  -------
                _lastSaw = _area[_coord.Y - 1][_coord.X - 1];           //  -------
            }                                                       // 15|14|13
        case 10:
            {
                _lastSaw = _area[_coord.Y - 1][_coord.X];
            }
        case 11:
            {
                _lastSaw = _area[_coord.Y - 1][_coord.X + 1];
            }
        case 12:
            {
                _lastSaw = _area[_coord.Y][_coord.X + 1];
            }
        case 13:
            {
                _lastSaw = _area[_coord.Y + 1][_coord.X + 1];
            }
        case 14:
            {
                _lastSaw = _area[_coord.Y + 1][_coord.X];
            }
        case 15:
            {
                _lastSaw = _area[_coord.Y + 1][_coord.X - 1];
            }
        case 16:
            {
                _lastSaw = _area[_coord.Y][_coord.X - 1];
            }
        default:
            break;
        }
    }
void Creation::_Mutation()
    {

        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> dist(0, 63);
        uniform_int_distribution<> dist2(1, COUNT_OF_COMMAND);

        _commandList[dist(gen)] = dist2(gen);
    }
bool Creation::_IsAlive()
    {
        if(_hp <= 0)
            return 0;

        return 1;
    }
void Creation::_Roll(UNI command)
    {
        _head = (direction) (command % 8);
    }
void Creation::AddSlots(Area* obj)
{
    _eatingFood.connect(boost::bind(&Area::minFood, obj));
    _eatingPoison.connect(boost::bind(&Area::minPoison, obj));
}