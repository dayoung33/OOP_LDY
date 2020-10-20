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
#include "Panel.h"
#include "TextInput.h"

#include <stdio.h>

using namespace std;

Position Position::up{ 0, 1 };
Position Position::down{ 0, -1 };
Position Position::right{ 1, 0 };
Position Position::left{ -1, 0 };
Position Position::zeros{ 0, 0 };
Position Position::ones{ 1, 1 };


int main()
{
	Screen& screen = *Screen::getInstance();
	InputManager& inputMgr = *InputManager::getInstance();
	vector<GameObject*> scene;

	auto panel = new Panel{ "", Position{3,3}, 10, 20, nullptr };
	new Block{ Position{4,0}, "\xdb  \xdb\xdb\xdb  \xdb", Position{ 3, 3},  panel };

	auto panel2 = new Panel{ " Next", Position{20, 3}, 10, 5, nullptr };
	new Block{ Position{5, 1}, "\xdb \xdb \xdb\xdb", Position{ 2, 3 }, panel2 };

	auto panel3 = new Panel{ " Score", Position{20, 19}, 10, 4, nullptr };
	int value = 0;
	auto score = new TextInput{ Position{4, 2}, value, panel3 };

	scene.push_back(panel);
	scene.push_back(panel2);
	scene.push_back(panel3);

	bool requestExit = false;


	while (requestExit == false)		
	{
		screen.clear();

		inputMgr.readInput();

		if (inputMgr.getKeyDown(VK_ESCAPE)) break;

		if (inputMgr.getKeyDown(VK_SPACE)) {
			value++;
			score->setValue(value);
		}

		for (auto object : scene) object->internalUpdate();
		for (auto object : scene) object->internalUpdatePos(false);
		for (auto object : scene) object->internalDraw();

		screen.render();

		inputMgr.consumeEvent();

		Sleep(100);	
	}

	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}
	