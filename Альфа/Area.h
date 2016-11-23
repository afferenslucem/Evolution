#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <Windows.h>
#include "Creation.h"

class Area
{
    vector<Creation> _crtns;   
	Prim** _area;
	int _heigh;//x
	int _width;//y

	void _craftArea()
	{
		COORD coord;
		for  (coord.Y = 0; coord.Y < this->_heigh; ++coord.Y)
			for (coord.X = 0; coord.X < this->_width; ++coord.X)
			{
				if (coord.X == 0 || coord.Y == 0 || coord.Y == this->_heigh - 1 || coord.X == this->_width - 1)
					this->SetWall(coord);
				else
					this->SetVoid(coord);
			}
	}
public:
	Area(){};
	Area(int heigh)
	{
		this->_heigh = heigh;
		this->_width = heigh * 1.5;

		this->_area = new  Prim*[this->_heigh];

		for (int i = 0; i < this->_heigh; ++i)
			this->_area[i] = new Prim[this->_width];

		this->_craftArea();

        int count = 0;

        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> rdWds(1, _width - 2);
        uniform_int_distribution<> rdHeigh(1, _heigh - 2);

        while(count < COUNT_OF_FOOD)
        {
            int x = rdWds(gen);
            int y = rdHeigh(gen);

            if(_area[y][x] == Void)
            {
               _area[y][x] = Food;
               count++;
            }
        }

        count = 0;

        while(count < COUNT_OF_POISON)
        {
            int x = rdWds(gen);
            int y = rdHeigh(gen);

            if(_area[y][x] == Void)
            {
               _area[y][x] = Poison;
               count++;
            }
        }
               
        cout << "Enter genom: ";

        vector<UNI> gens;

        for(int i = 0; i < 10; i++)
        {
            UNI gen2;
            cin >> gen2;
            gens.push_back(gen2);
        }
                                      
        uniform_int_distribution<> dist(24, 63);

        for(int i = 10; i < 64; i++)
            gens.push_back(dist(gen));

                  
        count = 0;
        while(count < COUNT_OF_CREATIONS)
        {
            int x = rdWds(gen);
            int y = rdHeigh(gen);

            
            if(_area[y][x] == Void)
            {                                                             
                COORD crd = {x, y};
                _crtns.push_back(Creation(crd, gens, _area, _heigh, _width));
                count++;
            }
        }
	}
	~Area() {};
	void SetEat(COORD coord)
	{
		this->_area[coord.Y][coord.X] = Food;
	}
	void SetPoison(COORD coord)
	{
		this->_area[coord.Y][coord.X] = Poison;
	}
	void SetWall(COORD coord)
	{
		this->_area[coord.Y][coord.X] = Wall;
	}
	void SetVoid(COORD coord)
	{
		this->_area[coord.Y][coord.X] = Void;
	}
	Prim** GetArea()
	{
		return _area;
	}
	void Print()
	{
		for (int y = 0; y < this->_heigh; ++y)
		{
			for (int x = 0; x < this->_width; ++x)
			{
				if(_area[y][x] == Wall)
                    cout << "W";
                if(_area[y][x] == Poison)
                    cout << "P";
                if(_area[y][x] == Food)
                    cout << "F";
                if(_area[y][x] == Crt)
                    cout << "C";
                if(_area[y][x] == Void)
                    cout << " ";
			}
			std::cout << std::endl;
		}
	}
	void Start()
    {
        int count = COUNT_OF_CREATIONS;

        while(count > MIN_COUNT_OF_CREATIONS)
        {
            count = COUNT_OF_CREATIONS;

            for(int i = 0; i < COUNT_OF_CREATIONS; i++)
            {
                if(_crtns[i].IsAlive())
                    _crtns[i].Execute();
                else count--;
            }

            system("cls");
            Print();
        }
    }
};