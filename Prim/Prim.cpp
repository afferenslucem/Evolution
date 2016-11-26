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
Color& Prim::getColor()
    {
        return this->_color;
    }
//--------------------------------

//Food
FoodC::FoodC():Prim(Food){}
FoodC::~FoodC(){}
//--------------------------------

//Poison
PoisonC::PoisonC():Prim(Poison){}
PoisonC::~PoisonC(){}
//--------------------------------

//Void
VoidC::VoidC():Prim(Void){}
VoidC::~VoidC(){}
//--------------------------------

//Wall
WallC::WallC():Prim(Wall){}
WallC::~WallC(){}
//--------------------------------

//Creation
CreationC::CreationC():Prim(Crt){} 
CreationC::~CreationC(){}
//--------------------------------

