#pragma once

#include "Area.h" 
    
	void Area::_craftArea()
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
    void Area::minFood()
    {
        _countOfFood--;
    }
    void Area::minPoison()
    {
        _countOfPoison--;
    }
	Area::Area(){};
	Area::Area(UNI x)
	{
		this->_heigh = x;
		this->_width = int (x * 1.5);
		this->_area = new  Prim*[this->_heigh];
		for (int i = 0; i < this->_heigh; ++i)
			this->_area[i] = new Prim[this->_width];
		this->_craftArea();
	}
	Area::~Area() {};
	void Area::SetFood(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Food;
	}
	void Area::SetPoison(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Poison;
	}
	void Area::SetWall(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Wall;
	}
	void Area::SetVoid(COORD coord)
	{
		this->_area[coord.X][coord.Y] = Void;
	}
	Prim** Area::GetArea()
	{
		return _area;
	}
	void Area::Print()
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