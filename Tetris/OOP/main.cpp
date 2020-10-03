// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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

	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}
	