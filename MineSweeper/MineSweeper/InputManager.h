#pragma once
#include <Windows.h>
class Screen;
class MineSweeper;
class InputManager
{
private:
	//Singleton
	InputManager();

public:
	static InputManager* GetInstance()
	{
		if (!instance)
			instance = new InputManager();		
		return instance;
	}

	~InputManager();

public:	
	void InputEvent();
	void SetScreen(Screen* _screen);
	void SetMineSweeper(MineSweeper* _mine);
private:
	VOID ErrorExit(const char *);
	VOID KeyEventProc(KEY_EVENT_RECORD);
	VOID MouseEventProc(MOUSE_EVENT_RECORD);
	VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

private:
	static InputManager* instance;
	Screen* screen;
	MineSweeper* mine;
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode;
	INPUT_RECORD irInBuf[128];
};

