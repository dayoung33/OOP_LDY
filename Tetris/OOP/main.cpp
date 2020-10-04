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
#include "Table.h"

#include <stdio.h>

using namespace std;

Table* table = Table::getInstance();
Screen* screen = Screen::getInstance();

void scoreDraw();
void GameOver();

int main()
{
	Borland::initialize();
	
	InputManager* inputMgr = InputManager::getInstance();


	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;
	//Block block;
	

	while (requestExit == false)		
	{
		screen->clear();

		if (table->getOver())
			break;

		inputMgr->readInput();

		table->start();
		table->update();
		table->draw();

		screen->render();

		inputMgr->consumeEvent();

		scoreDraw();

		Sleep(10);

	}

	GameOver();

	//printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}

void scoreDraw()
{
	Borland::gotoxy(30, 1); printf("+------------+");
	Borland::gotoxy(30, 2); printf("|            |");
	Borland::gotoxy(30, 3); printf("| SCORE :%3d |", table->getScore());
	Borland::gotoxy(30, 4); printf("|            |");
	Borland::gotoxy(30, 5); printf("| COMBO :%3d |", table->getCombo());
	Borland::gotoxy(30, 6); printf("|            |");
	Borland::gotoxy(30, 7); printf("| LEVEL :%3d |", table->getLevel());
	Borland::gotoxy(30, 8); printf("|            |");
	Borland::gotoxy(30, 9); printf("+------------+");
}

void GameOver()
{
	//screen->clear();
	system("cls");
	Borland::gotoxy(0, 1); printf("+------------+");
	Borland::gotoxy(0, 2); printf("|            |");
	Borland::gotoxy(0, 3); printf("|            |");
	Borland::gotoxy(0, 4); printf("| GAME  OVER |");
	Borland::gotoxy(0, 5); printf("|            |");
	Borland::gotoxy(0, 6); printf("| SCORE :%3d |", table->getScore());
	Borland::gotoxy(0, 7); printf("|            |");
	Borland::gotoxy(0, 8); printf("|            |");
	Borland::gotoxy(0, 9); printf("+------------+");
}