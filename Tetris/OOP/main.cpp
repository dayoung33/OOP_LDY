// main.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <Windows.h>

#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib> // include malloc,
#include <queue>

#include "Utils.h"
#include "Screen.h"
#include "InputManager.h"
#include "Block.h"
#include "Table.h"

#include <stdio.h>

using namespace std;

int main()
{
	Borland::initialize();
	Screen* screen = Screen::getInstance();
	InputManager* inputMgr = InputManager::getInstance();
	Table* table = Table::getInstance();

	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;
	//Block block;
	

	while (requestExit == false)		
	{
		screen->clear();
		//screen->SetTable();

		inputMgr->readInput();

		table->start();
		table->update();
		table->draw();

		screen->render();

		inputMgr->consumeEvent();

		Borland::gotoxy(30, 1);printf("+-----------+");
		Borland::gotoxy(30, 2);printf("|           |");
		Borland::gotoxy(30, 3);printf("| SCORE : %d |", table->getScore());
		Borland::gotoxy(30, 4);printf("|           |");
		Borland::gotoxy(30, 5);printf("| COMBO : %d |", table->getCombo());
		Borland::gotoxy(30, 6);printf("|           |");
		Borland::gotoxy(30, 7);printf("| LEVEL : %d |", table->getLevel());
		Borland::gotoxy(30, 8);printf("|           |");
		Borland::gotoxy(30, 9); printf("+-----------+");
		Sleep(10);
	}

	printf("\n���������� ����Ǿ����ϴ�.\n");
	return 0;
}
