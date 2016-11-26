#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <Windows.h>
#include "Creation.h"

class Area
{
	Prim** _area;
	UNI _heigh;//x
	UNI _width;//y
	UNI _countOfFood;
	UNI _countOfPoison;
    UNI countFP;
	void _craftArea();
public:
	Area();
	Area(UNI);
	~Area(); 
    void minFood();
    void minPoison();  
	void SetFood(COORD);
	void SetPoison(COORD);
	void SetWall(COORD);
	void SetVoid(COORD);
	Prim** GetArea();
	void Print();  	
};