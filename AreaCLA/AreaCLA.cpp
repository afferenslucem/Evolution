#include "AreaCLA.h"

AreaCLA::AreaCLA(int heigh)
{
	this->_heigh = heigh;
	this->_width = heigh * 1.5;
	this->_craftAreaCLA();
}

AreaCLA::~AreaCLA()
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

void AreaCLA::Print()
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

void AreaCLA::SetFood(COORD coord)
{
	delete this->_map[coord.Y][coord.X];
	this->_map[coord.Y][coord.X] = new PrimF;
}

void AreaCLA::SetPoison(COORD coord)
{
	delete this->_map[coord.Y][coord.X];
	this->_map[coord.Y][coord.X] = new PrimP;
}

void AreaCLA::SetVoid(COORD coord)
{
	delete this->_map[coord.Y][coord.X];
	this->_map[coord.Y][coord.X] = new PrimV;
}

void AreaCLA::SetWall(COORD coord)
{
	delete this->_map[coord.Y][coord.X];
	this->_map[coord.Y][coord.X] = new PrimW;
}

void AreaCLA::Start()
{

}

Prim*** AreaCLA::GetArea()
{
	return this->_map;
}

void AreaCLA::minFood()
{
	this->_countOfFood--;
}

void AreaCLA::minPoison()
{
	this->_countOfPoison--;
}
