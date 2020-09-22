#include "InputManager.h"

#include "Utils.h"
#include "Screen.h"
#include <stdio.h>

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
}

InputManager::~InputManager()
{
}

void InputManager::InputEvent()
{
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
	
	Borland::gotoxy(0, 21);
	printf("cNum  = %d" , cNumRead);

}

void InputManager::SetScreen(Screen * _screen)
{
	screen = _screen;
}

VOID InputManager::ErrorExit(const char *lpszMessage)
{
	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID InputManager::KeyEventProc(KEY_EVENT_RECORD ker)
{
	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');

	printf("Key event:  %c  %d             ", ker.uChar, ker.wRepeatCount);

	if (ker.bKeyDown)
		printf("key pressed\n");
	else printf("key released\n");
}

VOID InputManager::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif

	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');

	printf("Mouse event: %d  %d         ", mer.dwMousePosition.X, mer.dwMousePosition.Y);

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
			screen->Draw(mer.dwMousePosition.X, mer.dwMousePosition.Y, ' ');
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

VOID InputManager::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	Borland::gotoxy(0, 22);
	printf("%80\r", ' ');

	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
