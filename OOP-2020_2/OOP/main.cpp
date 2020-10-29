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


	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}
	