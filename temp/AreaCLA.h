#pragma once

#include <vector>
#include <Windows.h>
#include <random>  
#include "Prim.h"     
#include <fstream>    
#include "log.h"  
#include <thread>
#include <mutex>

#include "glut.h"
#include <gl/GL.h>
//#include "GLAux.h"
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "Glaux.lib")


using namespace std;

#define MIN_COUNT_OF_CRT 4
#define COUNT_OF_CRT 20

#define UNI unsigned short int

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

	CreationC** _crtns;
	int _crtnsCount;
	int _maxCrtnsCount;
	int _minCrtnsCount;


	void _craftAreaCLA();
	void _cicle();
	void _refresh();
	void _Reborn();
	void _chengeArea();

public: 
    mutex mut;
	AreaCLA(int heigh);
	~AreaCLA();
	void Print();
	void SetFood(COORD coord);
	void SetPoison(COORD coord);
	void SetWall(COORD coord);
	void SetVoid(COORD coord);
	void Start();
	
	void minFood();
	void minPoison();
	void delCrt(int, int, int);
	Prim*** GetArea();

	//for draw
	void DrawFulMap();
	void Init(int* argc, char** argv);
};
