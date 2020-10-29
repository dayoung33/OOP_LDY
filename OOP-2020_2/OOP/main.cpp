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
#include "GameManager.h"
#include "Panel.h"
#include "Text.h"
#include <stdio.h>

using namespace std;

Position Position::up	{  0, -1 };
Position Position::down	{  0,  1 };
Position Position::right{  1,  0 };
Position Position::left	{ -1,  0 };
Position Position::zeros{  0,  0 };
Position Position::ones	{  1,  1 };


int main()
{
	Screen& screen = *Screen::getInstance();
	InputManager& inputMgr = *InputManager::getInstance();
	GameManager& gameMgr = *GameManager::getInstance();

	bool requestExit = false;

	gameMgr.start();

	while (requestExit == false)		
	{
		screen.clear();

		inputMgr.readInput();

		gameMgr.update();
		gameMgr.draw();

		screen.render();

		inputMgr.consumeEvent();

		Sleep(100);	
	}


	printf("\n���������� ����Ǿ����ϴ�.\n");
	return 0;
}
	