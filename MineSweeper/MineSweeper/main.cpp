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
#include "MineSweeper.h"

#include <stdio.h>

//using namespace std;

int main()
{
	Borland::initialize();
	Screen* screen = Screen::GetInstance(10,10);
	InputManager* inputMgr = InputManager::GetInstance();
	inputMgr->SetScreen(screen);
	MineSweeper* minesweeper = MineSweeper::GetInstance(10,10);
	minesweeper->SetScreen(screen);
	inputMgr->SetMineSweeper(minesweeper);
	Borland::gotoxy(20, 0);
	minesweeper->InitMine();

	bool requestExit = false;
	int previousX = 0, previousY = 0;
	int x = 0, y = 0;


	screen->Clear();

	while (requestExit == false)		
	{
		Borland::gotoxy(0, 0);
		screen->Render();

		inputMgr->InputEvent();

		Borland::gotoxy(20, 1);
		printf("��� ���� : %d \n", screen->GetCheckNum());
		Borland::gotoxy(20, 2);
		printf("ã�� ���� : %d \n", minesweeper->GetFindMineNum());

		Sleep(100);	
	}

	printf("\n���������� ����Ǿ����ϴ�.\n");
	return 0;
}
	