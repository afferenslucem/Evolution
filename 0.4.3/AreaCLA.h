#pragma once
                    
#include <vector>
#include <Windows.h>
#include <random>  
#include "Prim.h"

#define MIN_COUNT_OF_CRT 4
#define COUNT_OF_CRT 20

#define UNI unsigned short int
using namespace std;

class Prim;
class CreationC;

class AreaCLA
{
    bool _countOfCtrnsChenged;
	Prim*** _map;
	int _heigh;//x
	int _width;//y
	UNI _countOfFood;
	UNI _countOfPoison;   
    UNI _FPCount;
    
    vector <CreationC*> _crtns;        

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
    void delCrt(CreationC*);// Удалить существо из вектора
	Prim*** GetArea();
};

