#pragma once
#include "Prim.h"
#include <iostream>
#include <windows.h> 
#include <vector>
#include <random>
#include <boost\signal.hpp>
#include <boost\bind.hpp> 

#define WallDamage 5
#define PoisonDamage 15
#define CrtDamage 3
#define FoodPlus 10
#define UNI unsigned short int

using namespace std;

enum Type {Void, Food, Poison, Wall, Crt};

struct Color
{
    int R;
    int G;
    int B;
    void operator=(Color& clr);
};

class Prim
{
protected:
    Type _type;
	int _x;
	int _y;
    int _healthPointChange;
    Color _color;
public:
	Type GetType();
	void SetType(Type);
	int GetX();
	int GetY();
	void SetX(int);
	void SetY(int);
	Prim();
	Prim(Type);
	virtual ~Prim() = 0;
    int getHPC();
    void setHPC(int);
    Color& getColor();
};

class FoodC : public Prim//Food
{

public:
    FoodC();
	~FoodC();
};

class PoisonC : public Prim//Pioson
{
public:
	PoisonC();
	~PoisonC();
};

class VoidC : public Prim//Void
{
public:
	VoidC();
	~VoidC();
};

class WallC : public Prim//Wall
{
public:
	WallC();
	~WallC();
};

class CreationC : public Prim//CRT
{
    enum direction {lU, up, uR, right, rD, dowm, dL, left};

    Type _lastSaw;
    direction _head;
    short int _hp;
    vector<UNI> _commandList; //[1; 8] - ходит [9; 16] - хавать 
    UNI _itForCommand;
    int _countOfStep;
    Prim*** _area;   
    
    boost::signal <void()> _eatingFood;
    boost::signal <void()> _eatingPoison;

    bool _IsClose(int X, int Y);
    //.......................................
    void _Step(UNI);
    void _See(UNI);
    void _Mutation();
    bool _IsAlive();
    void _Roll(UNI);
public:
    void Execute();
    void AddSlots();
	CreationC();
	~CreationC();
};
