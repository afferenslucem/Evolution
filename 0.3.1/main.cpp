#include "AreaCLA.h"

AreaCLA* area = new AreaCLA(20);





void func()
{
	 area->Start();
}

void Draw()
{
	glColor3i(0, 0, 1);
	area->DrawFulMap();
}

void start()
{
	area->Start();
}

int main(int argc, char** argv)
{
	thread thr(func);
	area->Init(&argc, argv);
	system("pause");
	return 0;
}