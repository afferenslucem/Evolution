#pragma once
#include "Prim.h"
#include <Windows.h>
#include <random>;
class AreaCLA
{
	Prim*** _map;
	int _heigh;//x
	int _width;//y
	UNI _countOfFood;
	UNI _countOfPoison;   
    UNI _FPCount;
    vector<Prim*> _crtns;         

	void _craftAreaCLA();
    void _cicle();
    void _refresh();

public:
	AreaCLA(int heigh);
	~AreaCLA();
	void Print();
	void SetFood(COORD coord);
	void SetPoison(COORD coord);
	void SetWall(COORD coord);
	void SetVoid(COORD coord);
	void Start();

	void minFood();//минус еда
	void minPoison();//минус яд
	Prim*** GetArea();
};

