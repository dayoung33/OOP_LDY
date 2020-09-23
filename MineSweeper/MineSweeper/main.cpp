// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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
	Screen* screen = Screen::GetInstance(9,9);
	InputManager* inputMgr = InputManager::GetInstance();
	inputMgr->SetScreen(screen);
	MineSweeper* minesweeper = MineSweeper::GetInstance(9,9);
	Borland::gotoxy(20, 0);
	minesweeper->InitMine();

	bool requestExit = false;
	char* temp = nullptr;
	int previousX = 0, previousY = 0;
	int x = 0, y = 0;


	screen->Clear();

	while (requestExit == false)		
	{
		Borland::gotoxy(0, 0);
		screen->Render();

		for (int i = 0; i < 81; i++) {
			if (minesweeper->GetData(i) == 9)
				screen->Draw(i%9,i/9, '@');
			else if (minesweeper->GetData(i) > 0) {
				_itoa_s(minesweeper->GetData(i),temp,sizeof(temp),10);
				//sprintf(temp, "%d", minesweeper->GetData(i));
				screen->Draw(i % 9, i / 9, *temp);
			}
		}

		inputMgr->InputEvent();

		Sleep(100);	
	}

	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}
	