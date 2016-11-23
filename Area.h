#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <Windows.h>

class Area
{
	Prim** _area;
	int _heigh;//x
	int _width;//y
	int _maxEat;
	int _maxPoison;
	void _craftArea()
	{
		COORD coord;
		for  (coord.X = 0; coord.X < this->_heigh; ++coord.X)
			for (coord.Y = 0; coord.Y < this->_width; ++coord.Y)
			{
				if (coord.X == 0 || coord.Y == 0 || coord.X == this->_heigh - 1 || coord.Y == this->_width - 1)
					this->SetWall(coord);
				else
					this->SetVoid(coord);
			}
	}
public:
	Area(){};
	Area(int x)
	{
		this->_heigh = x;
		this->_width = x * 1.5;
		this->_area = new  Prim*[this->_heigh];
		for (int i = 0; i < this->_heigh; ++i)
			this->_area[i] = new Prim[this->_width];
		this->_craftArea();
	}
	~Area() {};
	void SetEat(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Eat;
	}
	void SetPoison(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Poison;
	}
	void SetWall(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Wall;
	}
	void SetVoid(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Void;
	}
	Prim** GetArea()
	{
		return _area;
	}
	void Print()
	{
		for (int x = 0; x < this->_heigh; ++x)
		{
			for (int y = 0; y < this->_width; ++y)
			{
				std::cout << this->_area[x][y];

			}
			std::cout << std::endl;
		}
	}
	
};