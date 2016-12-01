#pragma once

#include "Prim.h"    
#include "log.h"   


void Color::operator=(Color& clr)
    {
        R = clr.R;
        G = clr.G;
        B = clr.B;
    }

// Base class
#pragma region prim funcs
Type Prim::GetType()
{
    return this->_type;
}
void Prim::SetType(Type type)
{
    
    _type = type;
    
    if(_type == Wall)
    {
        _healthPointChange = -WallDamage;
    }
    if(_type == Poison)
    {
        _healthPointChange = -PoisonDamage;
    }
    if(_type == Food)
    {
        _healthPointChange = FoodPlus;
    }
    if(_type == Crt)
    {
        _healthPointChange = -CrtDamage;
    }
    if(_type == Void)
    {
        _healthPointChange = 0;
    }
}
int Prim::GetX()
	{
		return this->_x;
	}
int Prim::GetY()
	{
		return this->_y;
	}
void Prim::SetX(int x)
	{
		this->_x = x;
	}
void Prim::SetY(int y)
	{
		this->_y = y;
	}
Prim::Prim(){}
Prim::Prim(Type type)
{
    _type = type;
    
    if(_type == Wall)
    {
        _healthPointChange = -WallDamage;
    }
    if(_type == Poison)
    {
        _healthPointChange = -PoisonDamage;
    }
    if(_type == Food)
    {
        _healthPointChange = FoodPlus;
    }
    if(_type == Crt)
    {
        _healthPointChange = -CrtDamage;
    }
    if(_type == Void)
    {
        _healthPointChange = 0;
    }
}
Prim::~Prim(){}
int Prim::getHPC()
    {
        return this->_healthPointChange;
    }   
void Prim::setHPC(int hpc)
    {
        _healthPointChange = hpc;
    }
Color& Prim::getColor()
    {
        return this->_color;
    }
#pragma endregion
//--------------------------------

//Creation
CreationC::CreationC(){}
CreationC::CreationC(vector<UNI>& gens, AreaCLA* world, int x, int y):Prim(Crt)
{                    
     random_device rd;   // non-deterministic generator  
     mt19937 gen(rd());  // to seed mersenne twister.  
     uniform_int_distribution<> rdHead(0, 7);

    _world = world;

    _itForCommand = 0;

    _countOfStep = 0;

    for(int i = 0; i < 64; i++)
        _commandList.push_back(gens[i]);
    _area = world->GetArea();
    _y = y;
    _x = x;
    _head = (direction) rdHead(gen);
    _hp = 10;
    _AddSlots();
} 
CreationC::~CreationC()
{
    _area[_y][_x] = nullptr;
}             
bool CreationC::_See(UNI command)
    {

        Type lastSaw;
        
        command = (command + _head + 7) % 8;

        switch (command)
        {               
        case 0:                                                     //  9|10|11
            {                                                       //  -------
                lastSaw = _area[_y - 1][_x - 1]->GetType();           //  -------
            }                                                       // 15|14|13
        case 1:
            {
                lastSaw = _area[_y - 1][_x]->GetType();
            }
        case 2:
            {
                lastSaw = _area[_y - 1][_x + 1]->GetType();
            }
        case 3:
            {
                lastSaw = _area[_y][_x + 1]->GetType();
            }
        case 4:
            {
                lastSaw = _area[_y + 1][_x + 1]->GetType();
            }
        case 5:
            {
                lastSaw = _area[_y + 1][_x]->GetType();
            }
        case 6:
            {
                lastSaw = _area[_y + 1][_x - 1]->GetType();
            }
        case 7:
            {
                lastSaw = _area[_y][_x - 1]->GetType();
            }
        default:
            break;
        }

        if(lastSaw == Food || lastSaw == Poison)
            return 1;

        return 0;
    }   
void CreationC::Mutation()
    {

        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> dist(1, 31);
        uniform_int_distribution<> dist2(1, 63);

        int count = dist2(gen), command = ((((gen() / dist(gen) + gen() / dist2(gen)) % (dist2(gen) * dist(gen)))) % 32);

        _commandList[count] = command;
    }
bool CreationC::IsAlive()
    {
        if(_hp <= 0)
            return 0;

        return 1;
    }
void CreationC::_Roll(UNI command)
    {
        _head = (direction) ((command + _head + 7) % 8);
    }
void CreationC::_AddSlots()
{
    _eatingFood.connect(boost::bind(&AreaCLA::minFood, _world));
    _eatingPoison.connect(boost::bind(&AreaCLA::minPoison, _world));
    
}   
void CreationC::Execute()
    {
        for(int i = 0; i < 10; i++)
        {
            if(_commandList[_itForCommand] > 0 && 7 >= _commandList[_itForCommand])
            {
                WLOG("                 Step")
                _Step(_commandList[_itForCommand]);  
                WLOG("                 EndStep")
                break;
            }
            
            if(_commandList[_itForCommand] > 7 && 15 >= _commandList[_itForCommand])
            {                    
                WLOG("                 Roll")
                _Roll(_commandList[_itForCommand]); 
                WLOG("                 EndRoll")
            }

            if(_commandList[_itForCommand] > 15 && 31 >= _commandList[_itForCommand]) // [16, 17, 18, 19, 20, 21, 22, 23]  [24, 25, 26, 27, 28, 29, 30, 31]
            {
                if(_See(_commandList[_itForCommand]))
                {               
                    WLOG("                 Eat")
                    _Eat(_commandList[_itForCommand]); 
                    WLOG("                 EndEat")
                }
            }
                           
            WLOG("                 ChengeCom: ")
            WLOG(_itForCommand)
                _itForCommand = (_itForCommand + _commandList[_itForCommand]) % 64;
            WLOG("                 EndChengeCom")
        }
        _hp--;
    }                                               
bool CreationC::_IsClose(int X, int Y)
    {
        if(_area[Y][X]->GetType() == Wall || _area[Y][X]->GetType() == Crt)
            return 1;

            return 0;
    }
vector<UNI>& CreationC::GetCommandList()
{
    return this->_commandList;
}
void CreationC::_Step(UNI command)
    {

        Prim* tempP = _area[_y][_x];
        int tempY = _y;
        int tempX = _x;

        if(_x < 0 || _y < 0)
            system("pause");

        command = (command + _head + 7) % 8;

        switch (command)
        {
        case 0:                          //  1|2|3
            {   
                if(_IsClose(_x - 1, _y - 1)) 
                {             
                    _hp += _area[_y - 1][_x - 1]->getHPC();; 
                    break;
                }
                _x -= 1;           //  8|X|4
                _y -= 1;  
                //  -------
                break;
            }                            //  7|6|5
        case 1:
            {     
                if(_IsClose(_x, _y - 1)) {
                    _hp += _area[_y - 1][_x]->getHPC();; 
                    break;
                }//            //  8|X|4
                _y -= 1;  
                //  -------
                break;
            }
        case 2:
            {         
                if(_IsClose(_x + 1, _y - 1)) {
                    _hp += _area[_y - 1][_x + 1]->getHPC();; 
                    break;
                }//  -------
                _x += 1;           //  8|X|4
                _y -= 1;  
                //  -------
                break;
            }
        case 3:
            {   
                if(_IsClose(_x + 1, _y)) {
                    _hp += _area[_y][_x + 1]->getHPC();; 
                    break;
                }//  
                _x += 1;   
                //  -------
                break;
            }
        case 4:                                   
            {    
                if(_IsClose(_x + 1, _y + 1)) 
                {
                    _hp += _area[_y + 1][_x + 1]->getHPC();; 
                    break;
                }//
                _x += 1;           //  8|X|4
                _y += 1;  
                //  -------
                break;
            }
        case 5:
            {   
                if(_IsClose(_x, _y + 1)) {
                    _hp += _area[_y + 1][_x]->getHPC();; 
                    break;
                }          //  8|X|4
                _y += 1;  
                //  -------
                break;
            }
        case 6:
            {        
                if(_IsClose(_x - 1, _y + 1)) {
                    _hp += _area[_y + 1][_x - 1]->getHPC();; 
                    break;
                }//  
                _x -= 1;           //  8|X|4
                _y += 1;  
                //  -------
                break;
            }
        case 7:
            {     
                if(_IsClose(_x - 1, _y)) {
                    _hp += _area[_y][_x - 1]->getHPC();; 
                    break;
                }//  
                _x -= 1;  
                //  -------
                break;
            }
        default:
            break;
        }


        if(_area[_y][_x]->GetType() == Food)
        {
            _eatingFood();
        }

        if(_area[_y][_x]->GetType() == Poison)
        {
            _eatingPoison();
        }
       
        if(tempX != _x || tempY != _y)
        {
            _hp += _area[_y][_x]->getHPC();           
        //старый указатель    //новый указатель
            _area[tempY][tempX] = _area[_y][_x];      
            _area[_y][_x] = tempP;

            _area[tempY][tempX]->SetType(Void);      

        }                 
            _countOfStep++;
    }
void CreationC::_Eat(UNI command)
{

    bool safe = 0;

    if(command < 24)
        safe = 0;
    else
        safe = 1;

    command = (command + _head + 7) % 8;

    int x, y;

        switch (command)
        {               
        case 0:                                                     //  9|10|11
            {                                                       //  -------
                y = _y - 1; x = _x - 1;          //  -------
            }                                                       // 15|14|13
        case 1:
            {
                y = _y - 1; x = _x;
            }
        case 2:
            {
                y = _y - 1; x = _x + 1;
            }
        case 3:
            {
                y = _y; x = _x + 1;
            }
        case 4:
            {
                y = _y + 1; x = _x + 1;
            }
        case 5:
            {
                y = _y + 1; x = _x;
            }
        case 6:
            {
                y = _y + 1; x = _x - 1;
            }
        case 7:
            {
                y = _y; x = _x - 1;
            }
        default:
            break;
        }


        if(_area[y][x]->GetType() == Poison)
        {
            if(safe)
            {
                _hp -= _area[y][x]->getHPC();
            }
            else
            {
                _hp += _area[y][x]->getHPC();
            }

            _area[y][x]->SetType(Void);
            _eatingPoison();
        }
        
        if(_area[y][x]->GetType() == Food)
        {
            _hp += _area[y][x]->getHPC(); 

            _area[y][x]->SetType(Void);

            _eatingFood();
        }          
}
//--------------------------------

