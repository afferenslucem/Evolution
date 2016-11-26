#pragma once     
#include "SimpleData.h"
#include "Area.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include <boost\signal.hpp>
#include <boost\bind.hpp> 

using namespace std;  

class Area;

class Creation
{     
private:   
    enum direction {lU, up, uR, right, rD, dowm, dL, left};

    Prim _lastSaw;
    direction _head;
    short int _hp;
    COORD _coord;
    vector<UNI> _commandList; //[1; 8] - ходит [9; 16] - хавать 
    UNI _itForCommand;
    Prim** _area;
    int _height;
    int _width;
    int _countOfStep;

    boost::signal <void()> _eatingFood;
    boost::signal <void()> _eatingPoison;
    
    bool _IsClose(int X, int Y)
    {
        if(_area[Y][X] == Wall || _area[Y][X] == Crt)
            return 1;

            return 0;
    }  
    //.......................................
    void _Step(UNI);
    void _See(UNI);
    void _Mutation();
    bool _IsAlive();
    void _Roll(UNI);


public: 
    void operator = (Creation&);
    Creation();
    Creation(COORD&, vector<UNI>&, Prim**, int, int);   
//    Creation(Creation& crt) = delete;
    ~Creation();
    void Execute();
    void AddSlots(Area*);
};