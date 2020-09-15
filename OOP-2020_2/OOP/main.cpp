// main.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib> // include malloc,

#include "Utils.h"
#include "Screen.h"

using namespace std;

// ���漱��

// �̱���
// Ŭ������ ������ �ν��Ͻ��� �ϳ��� �����ϵ��� ����� ��
// ������ �Լ��� �� �ѹ� �θ��� ��
// 0. ������ �Լ��� private�ϰ� ����
// 1. �ܺο� ����� Getinstance ��� static �Լ��� ����ϵ��� �����Ѵ� (������ �ּ� ��ȯ)
// 2. ���� ������ ��ü �ν��Ͻ��� ������ Instance ������  private�ϰ� ����

// static ���������� ��밡�� (�ʱ�ȭ�� �ѹ��� �ϴ� Ư¡)

// �̱����� ����ϴ� ����
// ���� ������� �ʴ´ٸ� �ƿ� �ν��Ͻ��� �������� �ʴ´�.
// ��Ÿ�ӿ� �ʱ�ȭ
// �̱����� ����� �� �ִ�.

int main()
{
	Borland::initialize();
	Screen* screen = Screen::GetInstance();

	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;

	while (requestExit == false)		
	{
		screen->Clear();

		x = rand() % 10;
		y = x;

		screen->Draw( x, y, '0' + x);

		Borland::gotoxy(20, 20);
		cout << "current x , y = " << x << " , " << y;

		Borland::gotoxy(0, 0);
		screen->Render();

		Sleep(1000);
		previousX = x;
		previousY = y;
		
	}
	printf("\n���������� ����Ǿ����ϴ�.\n");
	return 0;
}
