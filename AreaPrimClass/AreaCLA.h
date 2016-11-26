#pragma once
#include "Prim.h"
#include <Windows.h>
class AreaCLA
{
	Prim*** _map;
	int _heigh;//x
	int _width;//y
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
	AreaCLA(int heigh)
	{
		this->_heigh = heigh;
		this->_width = heigh * 1.5;
		this->_craftAreaCLA();
	}
	~AreaCLA()
	{
		COORD coord;
		for (coord.Y = 0; coord.Y < this->_heigh; ++coord.Y)
			for (coord.X = 0; coord.X < this->_width; ++coord.X)
			{
				delete this->_map[coord.Y][coord.X];
			}
		for (int i = 0; i < this->_heigh; ++i)
		{
			delete[] this->_map[i];
		}
		delete[] this->_map;
	}
	void Print()
	{
		for (int y = 0; y < this->_heigh; ++y)
		{
			for (int x = 0; x < this->_width; ++x)
			{
				this->_map[y][x]->GetPrim();
			}
			std::cout << std::endl;
		}
	}
	void PrintCOORD()
	{
		for (int y = 0; y < this->_heigh; ++y)
		{
			for (int x = 0; x < this->_width; ++x)
			{
				std::cout << "(" << this->_map[y][x]->GetX() << ":" << this->_map[y][x]->GetY() << ")";
			}
			std::cout << std::endl;
		}
	}
};

