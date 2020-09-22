// main.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <Windows.h>

//#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib> // include malloc,

#include "Utils.h"
#include "Screen.h"
#include "InputManager.h"

#include <stdio.h>

//using namespace std;

int main()
{
	Borland::initialize();
	Screen* screen = Screen::GetInstance();
	InputManager* inputMgr = InputManager::GetInstance();

	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;

	while (requestExit == false)		
	{
		screen->Clear();

		//screen->Draw( x, y, '0' + x);
		Borland::gotoxy(0, 0);
		screen->Render();

		inputMgr->InputEvent();

		Sleep(100);	
	}

	printf("\n���������� ����Ǿ����ϴ�.\n");
	return 0;
}
	