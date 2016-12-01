#pragma once

#include "AreaCLA.h"     
#include "log.h"  

mutex mut;
//for draw
void changeSize(int w, int h);
void Draw();
void init(int* argc, char** argv);
void start();
int Width;
int Height;

AreaCLA::AreaCLA(int heigh)
{
	mut.lock();
	this->_heigh = heigh;
	this->_width = (int)(heigh * 1.5);

	_maxCrtnsCount = _heigh * _width / 8;

	_maxCrtnsCount = _maxCrtnsCount - _maxCrtnsCount % 8;
	_minCrtnsCount = _maxCrtnsCount / 8;

	_crtnsCount = 0;

	_countOfFood = 0;
	_countOfPoison = 0;

	_FPCount = _heigh * _width / 12;

	_crtns = new CreationC*[_maxCrtnsCount];

	this->_craftAreaCLA();

	_countOfCtrnsChenged = 0;
	mut.unlock();
}
AreaCLA::~AreaCLA()
{
	out.close();
	for (int i = 0; i < _crtnsCount; i++)
	{
		if (_crtns[i])
			delete _crtns[i];
	}

	delete[] _crtns;

	COORD coord;
	for (coord.Y = 0; coord.Y < this->_heigh; ++coord.Y)
		for (coord.X = 0; coord.X < this->_width; ++coord.X)
		{
			if (_map[coord.Y][coord.X])
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
void AreaCLA::_chengeArea()
{
	LOG("ChengeAre")
		for (int y = 1; y < _heigh - 1; y++)
		{
			for (int x = 1; x < _width - 1; x++)
			{
				if (_map[y][x]->GetType() != Wall && _map[y][x]->GetType() != Crt && _map[y][x]->GetType() != Void)
				{
					_map[y][x]->SetType(Void);
				}
			}
		}
	_countOfPoison = 0;
	_countOfFood = 0;
	LOG("EndChengeAre")
}
void AreaCLA::_refresh()
{
	LOG("Refresh")
		random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> rdH(1, _heigh - 1);
	uniform_int_distribution<> rdW(1, _width - 1);

	int y, x;
	while (_countOfFood < _FPCount)
	{
		y = rdH(gen);
		x = rdW(gen);
		if (_map[y][x]->GetType() == Void)
		{
			_map[y][x]->SetType(Food);
			_countOfFood++;
		}
	}
	while (_countOfPoison < _FPCount)
	{
		y = rdH(gen);
		x = rdW(gen);
		if (_map[y][x]->GetType() == Void)
		{
			_map[y][x]->SetType(Poison);
			_countOfPoison++;
		}
	}
	LOG("EndRefresh")
}
void AreaCLA::Print()
{
	LOG("Print")
		for (int y = 0; y < this->_heigh; ++y)
		{
			for (int x = 0; x < this->_width; ++x)
			{
				if (this->_map[y][x]->GetType() == Wall)
					cout << "W";
				if (this->_map[y][x]->GetType() == Void)
					cout << " ";
				if (this->_map[y][x]->GetType() == Crt)
					cout << "C";
				if (this->_map[y][x]->GetType() == Food)
					cout << "F";
				if (this->_map[y][x]->GetType() == Poison)
					cout << "P";
			}
			std::cout << std::endl;
		}
	Sleep(50);
	LOG("EndPrint")
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
void AreaCLA::delCrt(int i, int x, int y)
{
	LOG("DelCrt")
		CreationC* temp;


	temp = _crtns[i];
	for (int j = i; j < _crtnsCount - 1; j++)
	{
		_crtns[j] = _crtns[j + 1];
	}
	_crtns[--_crtnsCount] = nullptr;

	_countOfCtrnsChenged = 1;

	delete temp;
	_map[y][x] = new Prim(Void);
	_map[y][x]->SetX(x);
	_map[y][x]->SetY(y);
	LOG("EndDelCrt")
}
void AreaCLA::_cicle()
{
	LOG("      StartCicle")
		for (int i = 0; i < _crtnsCount; i++)
		{
			if (!_crtns[i]) continue;

			LOG("           Execute")
				_crtns[i]->Execute();

			if (_crtns[i]->IsAlive() == 0)
				delCrt(i, _crtns[i]->GetX(), _crtns[i]->GetY());

			if (_crtnsCount == this->_minCrtnsCount)
				break;

			if (_countOfCtrnsChenged)
			{
				i--;
				_countOfCtrnsChenged = 0;
				continue;
			}
			LOG("           EndExecute")
		}
	LOG("      EndCicle")
}
void AreaCLA::_Reborn()
{
	LOG("Reborn")
		for (int i = 0; i < _crtnsCount / 4; i++)
			_crtns[i]->Mutation();

	CreationC** temp = new CreationC*[_maxCrtnsCount];

	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> rdH(1, _heigh - 2);
	uniform_int_distribution<> rdW(1, _width - 2);

	int x, y;

	int tempI = 0;


	for (int i = 0; i < _crtnsCount; i++)
	{// 3 * 7
		for (int j = 0; j < 8; j++)
		{
			while (true)
			{
				y = rdH(gen);
				x = rdW(gen);

				if (_map[y][x]->GetType() == Void)
				{
					delete _map[y][x];

					_map[y][x] = new CreationC(this->_crtns[i]->GetCommandList(), this, x, y);
					temp[i * (8) + j] = (CreationC*)_map[y][x];
					tempI++;

					break;
				}
			}
		}

	}

	int tempI2 = _crtnsCount;

	for (int i = tempI2 - 1; i >= 0; i--)
	{
		delCrt(i, _crtns[i]->GetX(), _crtns[i]->GetY());
	}

	delete _crtns;

	_crtnsCount = tempI;

	_countOfCtrnsChenged = 0;

	_crtns = temp;
	LOG("EndReborn")
}
void AreaCLA::Start()
{
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> rdH(1, _heigh - 2);
	uniform_int_distribution<> rdW(1, _width - 2);
	mut.lock();
	int g;
	vector<UNI> gens;
	/*cout << "Enter gens: ";
	for (int i = 0; i < 10; i++)
	{
		cin >> g;
		gens.push_back(g);
	}*/
	for (int i = 0; i < 10; ++i)
	{
		gens.push_back(i);
	}
	
	mut.unlock();
	uniform_int_distribution<> dist(1, 40);
	uniform_int_distribution<> dist2(1, 100);

	while (gens.size() < 64)
		gens.push_back((((gen() / dist(gen) + gen() / dist2(gen)) % (dist2(gen) * dist(gen)))) % 32);

	int x, y;
	while (_crtnsCount < _maxCrtnsCount)
	{
		y = rdH(gen);
		x = rdW(gen);

		if (_map[y][x]->GetType() == Void)
		{
			delete _map[y][x];

			_map[y][x] = new CreationC(gens, this, x, y);
			_crtns[_crtnsCount++] = (CreationC*)_map[y][x];
		}
	}

	int generanionNum = 0;


	while (1)
	{
		out.open("logs.txt");
		generanionNum++;

		LOG("generation ")

			cout << generanionNum << " generaton" << endl;;
		Sleep(1);

	//	system("cls");

		while (_crtnsCount > _minCrtnsCount)
		{
			LOG("cicle")
				_cicle();

			LOG("refresh")
				_refresh();

			LOG("print")
			//	Print();

		//	system("cls");
		}
		_chengeArea();
		_refresh();
		_Reborn();
		out.close();
	}
//	cout << _crtnsCount << endl;
}

//for draw
void AreaCLA::Init(int* argc, char** argv)
{
	
	
	//craft Window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(this->_width * 16, this->_heigh * 16);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Evolution");
	FreeConsole();
	//Registratoin func
	glutDisplayFunc(Draw);
	glutReshapeFunc(changeSize);
	glutIdleFunc(Draw);
	//main loop
	glutMainLoop();
	
}


void AreaCLA::DrawFulMap()
{
	for (int y = 0; y < this->_heigh; ++y)
	{
		for (int x = 0; x < this->_width; ++x)
		{
			if (this->_map[y][x]->GetType() == 3)
				glColor3f(0, 0, 0);
			if (this->_map[y][x]->GetType() == 0)
				glColor3f(1, 1, 1);
			if (this->_map[y][x]->GetType() == 1)
				glColor3f(0, 1, 0);
			if (this->_map[y][x]->GetType() == 2)
				glColor3f(1, 0, 0);
			if (this->_map[y][x]->GetType() == 4)
				glColor3ub(255, 192, 203);
			glRecti(this->_map[y][x]->GetX() * 16, this->_map[y][x]->GetY() * 16, this->_map[y][x]->GetX() * 16 + 16, this->_map[y][x]->GetY() * 16 + 16);
			glFinish();
		}
	}
	glFinish();
	/*glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	for (float i = 0; i < this->_width * 16; i += 16.0)
	{
		glVertex2f(i, 0);
		glVertex2f(i, this->_width * 11);
		glFinish();
	}
	for (float i = 0; i < this->_heigh * 16; i += 16.0)
	{
		glVertex2f(0, i);
		glVertex2f(this->_heigh * 24, i);
		glFinish();
	}
	glEnd();
	glFinish();*/
}


void changeSize(int w, int h)//функция для корректного отображения после изменение размеров окна
{
	Width = w;
	Height = h;

	/* устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);

	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}