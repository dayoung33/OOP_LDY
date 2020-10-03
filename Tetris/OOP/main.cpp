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

#include <stdio.h>

using namespace std;

int main()
{
	Borland::initialize();
	Screen* screen = Screen::getInstance();
	InputManager* inputMgr = InputManager::getInstance();


	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;
	Block block;

	while (requestExit == false)		
	{
		screen->clear();
		screen->SetTable();

		inputMgr->readInput();

		block.update();
		block.draw();

		screen->render();

		inputMgr->consumeEvent();

		Sleep(10);	
	}

	printf("\n���������� ����Ǿ����ϴ�.\n");
	return 0;
}
	