#pragma once
#include "Prim.h"
#include <Windows.h>
#include <random>;
class AreaCLA
{
	Prim*** _map;
	int _heigh;//x
	int _width;//y
	unsigned int _countOfFood;
	unsigned int _countOfPoison;
	void _craftAreaCLA()
	{
		this->_map = new Prim**[this->_heigh];
		for (int i = 0; i < this->_heigh; ++i)
		{
			this->_map[i] = new Prim*[this->_width];
		}
		COORD coord;
		for (coord.Y = 0; coord.Y < this->_heigh; ++coord.Y)
			for (coord.X = 0; coord.X < this->_width; ++coord.X)
			{
				if (coord.X == 0 || coord.Y == 0 || coord.Y == this->_heigh - 1 || coord.X == this->_width - 1)
				{
					this->_map[coord.Y][coord.X] = new PrimW;
				}
				else
				{
					this->_map[coord.Y][coord.X] = new PrimV;
				}
				this->_map[coord.Y][coord.X]->SetX(coord.X);
				this->_map[coord.Y][coord.X]->SetY(coord.Y);
			}
	}
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

