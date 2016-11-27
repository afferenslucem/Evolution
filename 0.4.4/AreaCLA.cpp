#pragma once

#include "AreaCLA.h"

AreaCLA::AreaCLA(int heigh)
{
	this->_heigh = heigh;
	this->_width = (int) (heigh * 1.5);
	this->_craftAreaCLA();

    _countOfCtrnsChenged = 0;
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
void AreaCLA::_craftAreaCLA()
	{

        _countOfFood = 0;
        _countOfPoison = 0;

        _FPCount = _heigh * _width / 8;

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
					this->_map[coord.Y][coord.X] = new Prim(Wall);
				}
				else
				{
					this->_map[coord.Y][coord.X] = new Prim(Void);
				}
				this->_map[coord.Y][coord.X]->SetX(coord.X);
				this->_map[coord.Y][coord.X]->SetY(coord.Y);
			}
        
        _refresh();

	}  
void AreaCLA::_refresh()
{
    random_device rd;   // non-deterministic generator  
    mt19937 gen(rd());  // to seed mersenne twister.  
    uniform_int_distribution<> rdH(0, _heigh - 1);
    uniform_int_distribution<> rdW(0, _width - 1);

    int y, x;
    while(_countOfFood < _FPCount)
    {
        y = rdH(gen);
        x = rdW(gen);
        if(_map[y][x]->GetType() == Void)
        {
            _map[y][x]->SetType(Food);
            _countOfFood++;
        }
    }
    while(_countOfPoison < _FPCount)
    {
        y = rdH(gen);
        x = rdW(gen);
        if(_map[y][x]->GetType() == Void)
        {
            _map[y][x]->SetType(Poison);
            _countOfPoison++;
        }
    }
}
void AreaCLA::Print()
{
	for (int y = 0; y < this->_heigh; ++y)
	{
		for (int x = 0; x < this->_width; ++x)
		{
            this->_map[y][x]->GetType();
		}
		std::cout << std::endl;
	}
}                
void AreaCLA::SetFood(COORD coord)
{
    this->_map[coord.Y][coord.X]->SetType(Food);
}        
void AreaCLA::SetPoison(COORD coord)
{
	delete this->_map[coord.Y][coord.X];
	this->_map[coord.Y][coord.X] = new Prim(Poison);
}    
void AreaCLA::SetVoid(COORD coord)
{
    this->_map[coord.Y][coord.X]->SetType(Void);
}            
void AreaCLA::SetWall(COORD coord)
{
    this->_map[coord.Y][coord.X]->SetType(Wall);
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
void AreaCLA::_cicle()
{
    for(int i = 0; i < _crtns.size(); i++)
    {
        ((CreationC*)_crtns[i])->Execute();
        if(_countOfCtrnsChenged) i--;
    }
}
void AreaCLA::delCrt(CreationC* crt)
{
    vector<CreationC*>::iterator it = find(_crtns.begin(), _crtns.end(), crt);
    int x, y;
    y = (*it)->GetY();
    x = (*it)->GetX();
    _crtns.erase(it);
    
    _countOfCtrnsChenged = 1;

    delete _map[y][x];
    _map[y][x] = new Prim(Void);
}
void AreaCLA::Start()
{
     random_device rd;   // non-deterministic generator  
     mt19937 gen(rd());  // to seed mersenne twister.  
     uniform_int_distribution<> rdH(1, _heigh - 2);
     uniform_int_distribution<> rdW(1, _width - 2);

     int g;
     vector<UNI> gens;
     cout << "Enter gens: ";
     for(int i = 0; i < 10; i++)
     {
         cin >> g;
         gens.push_back(g);
     }          

     uniform_int_distribution<> dist(24, 63);

     while(gens.size() < 64)
         gens.push_back(dist(gen));

     int x, y;
     while(_crtns.size() < COUNT_OF_CRT)
     {
         y = rdH(gen);
         x = rdW(gen);

         if(_map[y][x]->GetType() == Void)
         {
             delete _map[y][x];

             _map[y][x] = new CreationC(gens, _map, x, y);
             (( CreationC*)_map[y][x])->AddSlots(this);
             _crtns.push_back((CreationC*) _map[y][x]);
         }
     }

         while(_crtns.size() > MIN_COUNT_OF_CRT)
         {
             _cicle();
             _refresh();
         }

      cout << _crtns.size() << endl;
}
