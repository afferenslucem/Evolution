#pragma once
#include "Prim.h"
#include <iostream>
class PrimV;

class Prim
{
	int _x;
	int _y;
public:
	void GetPrim()
	{
		std::cout << "Base";
	}
	int GetX()
	{
		return this->_x;
	}
	int GetY()
	{
		return this->_y;
	}
	void SetX(int x)
	{
		this->_x = x;
	}
	void SetY(int y)
	{
		this->_y = y;
	}
	Prim(){}
	virtual ~Prim(){}
};

class PrimF : public Prim//Food
{

public:
	void GetPrim()
	{
		std::cout << "Food";
	}
	PrimF(){}
	~PrimF(){}
};

class PrimP : public Prim//Pioson
{
public:
	void GetPrim()
	{
		std::cout << "Pioson";
	}
	PrimP(){}
	~PrimP(){}
};

class PrimV : public Prim//Void
{
public:
	void GetPrim()
	{
		std::cout << "Void";
	}
	PrimV(){}
	~PrimV(){}
};

class PrimW : public Prim//Wall
{
public:
	void GetPrim()
	{
		std::cout << "Wall";
	}
	PrimW(){}
	~PrimW(){}
};

class PrimC : public Prim//CRT
{
public:
	void GetPrim()
	{
		std::cout << "Bot";
	}
	PrimC(){}
	~PrimC(){}
};
