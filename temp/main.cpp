#include "AreaCLA.h"

AreaCLA* area;
                                        
void func()
{
	 area->Start();
}

void Draw()
{
	glColor3i(0, 0, 0);
	area->DrawFulMap();
}

void start()
{
	area->Start();
}

int main(int argc, char** argv)
{
    int heigh;
    cout << "Enter area`s heigh: "; cin >> heigh;
    area  = new AreaCLA(heigh);
	thread thr(func);
	area->Init(&argc, argv);
	system("pause");
	return 0;
}