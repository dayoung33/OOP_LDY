// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib> // include malloc,

#include "Utils.h"
#include "Screen.h"

using namespace std;

// 전방선언

// 싱글톤
// 클래스로 생성된 인스턴스가 하나만 존재하도록 만드는 것
// 생성자 함수를 딱 한번 부르는 것
// 0. 생성자 함수를 private하게 선언
// 1. 외부에 노축된 Getinstance 라는 static 함수를 사용하도록 강제한다 (변수의 주소 변환)
// 2. 동적 생성된 객체 인스턴스를 저장할 Instance 변수를  private하게 선언

// static 지역변수도 사용가능 (초기화를 한번만 하는 특징)

// 싱글톤을 사용하는 이유
// 만약 사용하지 않는다면 아예 인스턴스를 생성하지 않는다.
// 런타임에 초기화
// 싱글톤을 상속할 수 있다.

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
	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}
