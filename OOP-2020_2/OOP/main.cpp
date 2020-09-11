// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib> // include malloc,

#include "Utils.h"
#include "Screen.h"

using namespace std;

int main()
{
	Borland::initialize();
	Screen screen(10, 10);

	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;

	while (requestExit == false)		
	{
		screen.Clear();

		x = rand() % 10;
		y = x;

		screen.Draw( x, y, '0' + x);

		Borland::gotoxy(20, 20);
		cout << "current x , y = " << x << " , " << y;

		Borland::gotoxy(0, 0);
		screen.Render();

		Sleep(1000);
		previousX = x;
		previousY = y;
		
	}
	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}
