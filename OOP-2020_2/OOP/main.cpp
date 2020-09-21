// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <Windows.h>

//#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib> // include malloc,

#include "Utils.h"
#include "Screen.h"

#include <stdio.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(const char *);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

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

	DWORD cNumRead, fdwMode;
	INPUT_RECORD irInBuf[128];

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	bool requestExit = false;

	int previousX = 0, previousY = 0;
	int x = 0, y = 0;

	while (requestExit == false)		
	{
		screen->Clear();

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 

		for (int i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}


		//screen->Draw( x, y, '0' + x);
		Borland::gotoxy(0, 0);
		screen->Render();

		Borland::gotoxy(0, 21);
		printf("cNum  = %d" , cNumRead);


		Sleep(100);	
	}

	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}

VOID ErrorExit(const char* lpszMessage)
{
	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');
	
	printf("Key event:  %c  %d             ",ker.uChar,ker.wRepeatCount);

	if (ker.bKeyDown)
		printf("key pressed\n");
	else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif

	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');

	printf("Mouse event: %d  %d         ",mer.dwMousePosition.X,mer.dwMousePosition.Y);

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');

	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}