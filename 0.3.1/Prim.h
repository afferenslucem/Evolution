#pragma once
#include "AreaCLA.h"
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

enum Type { Void, Food, Poison, Wall, Crt };

class AreaCLA;

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
	~Prim();
	int getHPC();
	void setHPC(int);
	Color& getColor();
};

class CreationC : public Prim//CRT
{
	enum direction { lU, up, uR, right, rD, dowm, dL, left };

	AreaCLA* _world;
	direction _head;
	short int _hp;
	vector<UNI> _commandList; //[1; 8] - õîäèò [9; 16] - õàâàòü 
	UNI _itForCommand;
	int _countOfStep;
	Prim*** _area;

	boost::signal <void()> _eatingFood;
	boost::signal <void()> _eatingPoison;

	bool _IsClose(int X, int Y);
	//.......................................
	void _Step(UNI);
	bool _See(UNI);
	void _Roll(UNI);
	void _AddSlots();
	void _Eat(UNI);
public:
	void Mutation();
	bool IsAlive();
	void Execute();
	CreationC(vector<UNI>& gens, AreaCLA*, int x, int y);
	CreationC();
	vector<UNI>& GetCommandList();
	~CreationC();
};