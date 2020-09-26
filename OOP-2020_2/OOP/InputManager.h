#pragma once
#include <Windows.h>
#include <queue>
using namespace std;

class InputManager
{
private:
	//Singleton
	InputManager();

public:
	static InputManager* getInstance()
	{
		if (!instance)
			instance = new InputManager();		
		return instance;
	}

	~InputManager();

public:	
	void readInput();
	void consumeEvent();
	bool getKeyDown(WORD ch);

private:
	VOID ErrorExit(const char *);
	VOID KeyEventProc(KEY_EVENT_RECORD);
	VOID MouseEventProc(MOUSE_EVENT_RECORD);
	VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

private:
	static InputManager* instance;
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode;
	INPUT_RECORD irInBuf[128];

	deque<INPUT_RECORD> events;

};

