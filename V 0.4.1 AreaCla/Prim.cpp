#pragma once

#include "Prim.h"


void Color::operator=(Color& clr)
    {
        R = clr.R;
        G = clr.G;
        B = clr.B;
    }

// Base class
Type Prim::GetType()
{
    return this->_type;
}
void Prim::SetType(Type type)
{
    
    _type = type;
    
    if(_type == Wall)
    {
        _healthPointChange = -WallDamage;
    }
    if(_type == Poison)
    {
        _healthPointChange = -PoisonDamage;
    }
    if(_type == Food)
    {
        _healthPointChange = FoodPlus;
    }
    if(_type == Crt)
    {
        _healthPointChange = -CrtDamage;
    }
    if(_type == Void)
    {
        _healthPointChange = 0;
    }
}
int Prim::GetX()
	{
		return this->_x;
	}
int Prim::GetY()
	{
		return this->_y;
	}
void Prim::SetX(int x)
	{
		this->_x = x;
	}
void Prim::SetY(int y)
	{
		this->_y = y;
	}
Prim::Prim(){}
Prim::Prim(Type type)
{
    _type = type;
    
    if(_type == Wall)
    {
        _healthPointChange = -WallDamage;
    }
    if(_type == Poison)
    {
        _healthPointChange = -PoisonDamage;
    }
    if(_type == Food)
    {
        _healthPointChange = FoodPlus;
    }
    if(_type == Crt)
    {
        _healthPointChange = -CrtDamage;
    }
    if(_type == Void)
    {
        _healthPointChange = 0;
    }
}
Prim::~Prim(){}
int Prim::getHPC()
    {
        return this->_healthPointChange;
    }   
void Prim::setHPC(int hpc)
    {
        _healthPointChange = hpc;
    }
Color& Prim::getColor()
    {
        return this->_color;
    }
//--------------------------------

//Creation
CreationC::CreationC():Prim(Crt){} 
CreationC::~CreationC(){}

bool CreationC::_IsClose(int X, int Y)
    {
        if(_area[Y][X]->GetType() == Wall || _area[Y][X]->GetType() == Crt)
            return 1;

            return 0;
    }
void CreationC::_Step(UNI command)
    {

        Prim* tempP = _area[_y][_x];
        int tempY = _y;
        int tempX = _x;


        command = (command + _head + 7) % 8;

        switch (command)
        {
        case 0:                          //  1|2|3
            {   
                if(_IsClose(_x - 1, _y - 1)) 
                {             
                    _hp += _area[_y - 1][_x - 1]->getHPC();; 
                    break;
                }
                _x -= 1;           //  8|X|4
                _y -= 1;  
                //  -------
                break;
            }                            //  7|6|5
        case 1:
            {     
                if(_IsClose(_x, _y - 1)) {
                    _hp += _area[_y - 1][_x]->getHPC();; 
                    break;
                }//            //  8|X|4
                _y -= 1;  
                //  -------
                break;
            }
        case 2:
            {         
                if(_IsClose(_x + 1, _y - 1)) {
                    _hp += _area[_y - 1][_x + 1]->getHPC();; 
                    break;
                }//  -------
                _x += 1;           //  8|X|4
                _y -= 1;  
                //  -------
                break;
            }
        case 3:
            {   
                if(_IsClose(_x + 1, _y)) {
                    _hp += _area[_y][_x + 1]->getHPC();; 
                    break;
                }//  
                _x += 1;   
                //  -------
                break;
            }
        case 4:                                   
            {    
                if(_IsClose(_x + 1, _y + 1)) 
                {
                    _hp += _area[_y + 1][_x + 1]->getHPC();; 
                    break;
                }//
                _x += 1;           //  8|X|4
                _y += 1;  
                //  -------
                break;
            }
        case 5:
            {   
                if(_IsClose(_x, _y + 1)) {
                    _hp += _area[_y + 1][_x]->getHPC();; 
                    break;
                }          //  8|X|4
                _y += 1;  
                //  -------
                break;
            }
        case 6:
            {        
                if(_IsClose(_x - 1, _y + 1)) {
                    _hp += _area[_y + 1][_x - 1]->getHPC();; 
                    break;
                }//  
                _x -= 1;           //  8|X|4
                _y += 1;  
                //  -------
                break;
            }
        case 7:
            {     
                if(_IsClose(_x - 1, _y)) {
                    _hp += _area[_y][_x - 1]->getHPC();; 
                    break;
                }//  
                _x -= 1;  
                //  -------
                break;
            }
        default:
            break;
        }


        if(_area[_y][_x]->GetType() == Food)
        {
            _eatingFood();
        }

        if(_area[_y][_x]->GetType() == Poison)
        {
            _eatingPoison();
        }
       
        //старый указатель 
        //новый указатель
        

        _area[tempY][tempY] = _area[_y][_x];
        _area[_y][_x] = tempP;

        _area[tempY][tempY]->SetType(Void);

        _countOfStep++;  
        _hp--;
    }
void CreationC::_See(UNI command)
    {

        command = (command + _head + 7) % 8;

        switch (command)
        {               
        case 0:                                                     //  9|10|11
            {                                                       //  -------
                _lastSaw = _area[_y - 1][_x - 1]->GetType();           //  -------
            }                                                       // 15|14|13
        case 1:
            {
                _lastSaw = _area[_y - 1][_x]->GetType();
            }
        case 2:
            {
                _lastSaw = _area[_y - 1][_x + 1]->GetType();
            }
        case 3:
            {
                _lastSaw = _area[_y][_x + 1]->GetType();
            }
        case 4:
            {
                _lastSaw = _area[_y + 1][_x + 1]->GetType();
            }
        case 5:
            {
                _lastSaw = _area[_y + 1][_x]->GetType();
            }
        case 6:
            {
                _lastSaw = _area[_y + 1][_x - 1]->GetType();
            }
        case 7:
            {
                _lastSaw = _area[_y][_x - 1]->GetType();
            }
        default:
            break;
        }
    }
void CreationC::_Mutation()
    {

        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> dist(0, 63);

        int count = dist(gen), command = dist(gen);

        _commandList[count] = command;
    }
bool CreationC::_IsAlive()
    {
        if(_hp <= 0)
            return 0;

        return 1;
    }
void CreationC::_Roll(UNI command)
    {
        _head = (direction) ((command + _head + 7) % 8);
    }
void CreationC::AddSlots()
{
    //_eatingFood.connect(boost::bind(&Area::minFood, obj));
    //_eatingPoison.connect(boost::bind(&Area::minPoison, obj));
}
//--------------------------------

