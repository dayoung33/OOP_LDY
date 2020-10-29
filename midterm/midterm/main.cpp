// main.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib> 
#include <deque>
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

// forward declaration

class Screen {
	int width;
	int height;
	char* buffer;

	Screen(int w = 10, int h = 10)
		: width(w), height(h), buffer{ new char[getSize()] }
	{	
		Borland::initialize();
		buffer[getSize() - 1] = '\0';
	}
	static Screen* instance;

public:

	static Screen* getInstance() {
		if (instance == nullptr) {
			instance = new Screen{ 80, 30 };
		}
		return instance;
	}

	~Screen() { delete[] buffer; }

	int getWidth() const { return width; }
	int getScreenWidth() const { return width + 1; }
	int getHeight() const { return height; }
	int getSize() const { return getScreenWidth()*height; }

	void clear() { memset(buffer, ' ', getSize()); buffer[getSize() - 1] = '\0';  }

	void draw(int x, int y, const char shape) { buffer[y* getScreenWidth() + x] = shape; }
	void draw(int x, int y, const char* shape, int len) {
		if (shape == nullptr || len == 0 || len > strlen(shape) ) return;
		strncpy(&buffer[y* getScreenWidth() + x], shape, len);
	}
	void draw(const Position& pos, char shape) { draw(pos.x, pos.y, shape); }
	void draw(const Position& pos, const char* shape) { draw(pos.x, pos.y, shape, strlen(shape)); }
	void draw(const Position& pos, const char* shape, int len) { draw(pos.x, pos.y, shape, len); }
	void drawLineHorizontal(const Position& pos, int width) {
		if (pos.x < 0 || pos.y < 0 || pos.x + width > getWidth() || pos.y > getHeight()) return;
		for (int i = pos.x; i <= min(this->width, pos.x + width); i++) draw(i, pos.y, 196);
	}
	void drawLineVertical(const Position& pos, int height) {
		if (pos.x < 0 || pos.y < 0 || pos.x > getWidth() || pos.y + height > getHeight()) return;
		for (int i = pos.y; i <= min(this->height,  pos.y + height); i++) draw(pos.x, i, 179);
	}
	void drawRectangle(const Position& topLeft, const Position& sz) {
		drawLineHorizontal(topLeft, sz.x);
		drawLineHorizontal(topLeft + Position{ 0, sz.y }, sz.x);
		drawLineVertical(topLeft, sz.y);
		drawLineVertical(topLeft + Position{ sz.x, 0 }, sz.y);
		draw(topLeft, 218); draw(topLeft + Position{ sz.x, 0 }, 191);
		draw(topLeft + Position{ 0, sz.y }, 192); draw(topLeft + sz, 217);
	}
	void drawShape(const Position& pos, const Position& sz, const char* shape)
	{
		if (shape == nullptr) return;
		for (int i = 0; i < sz.y; i++) draw(pos.x, pos.y+i, &shape[i*sz.x], sz.x);
	}

	void render()
	{
		for (int y = 0; y < height - 1; y++) 
			draw(width, y, '\n');
		draw(width - 1, height, '\0');

		Borland::gotoxy(0, 0);
		cout << buffer;
	}
};

Screen* Screen::instance = nullptr;

// �̱���
// Ŭ������ ������ �ν��Ͻ��� �ϳ��� �����ϵ��� ����� ��.
// ������ �Լ��� �� �ѹ� �θ��� ��
// �̱��� ����
// 0. ������ �Լ��� private�ϰ� ����
// 1. �ܺο� ����� getInstance��� static �Լ��� ����ϵ��� �����Ѵ�.(������ �ּ� ��ȯ)
// 2. ���� ������ ��ü �ν��Ͻ��� ������ instance ������ private�ϰ� ����

// ����ϴ� ����
// ���� ������� �ʴ´ٸ� �ƿ� �ν��Ͻ��� �������� �ʴ´�.
// ��Ÿ�ӿ� �ʱ�ȭ�ȴ�.
// �̱����� ����� �� �ִ�.


// singleton
class InputManager {

	INPUT_RECORD irInBuf[128];

	HANDLE hStdin;
	DWORD fdwSaveOldMode;

	deque<INPUT_RECORD> events;

	InputManager() : hStdin(GetStdHandle(STD_INPUT_HANDLE)), irInBuf{ {0} }	{
		if (hStdin == INVALID_HANDLE_VALUE) return;
		FlushConsoleInputBuffer(hStdin);

		string mode = "mode con:cols=" + to_string(Screen::getInstance()->getWidth() + 10);
		mode += " lines=" + to_string(Screen::getInstance()->getHeight() + 5);
		std::system(mode.c_str());
		std::system("chcp 437");

		if (!GetConsoleMode(hStdin, &fdwSaveOldMode)) return;
		if (!SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) return;
		events.clear();
	}

	VOID ErrorExit(const char* lpszMessage)
	{
		Borland::gotoxy(0, 21);
		printf("%80d\r", ' ');
		printf("%s\n", lpszMessage);

		// Restore input mode on exit.

		SetConsoleMode(hStdin, fdwSaveOldMode);

		ExitProcess(0);
	}

	VOID KeyEventProc(KEY_EVENT_RECORD ker)
	{
		if (ker.bKeyDown)
			printf("key pressed\n");
		else
			printf("key released\n");
	}

	VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
	{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
		Borland::gotoxy(0, 29);
		printf("%80d\r", ' ');

		printf("Mouse event: %d %d      ", mer.dwMousePosition.X, mer.dwMousePosition.Y);

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

	static InputManager* instance;
public:
	static InputManager* getInstance() {
		if (instance == nullptr) {
			instance = new InputManager;
		}
		return instance;
	}

	bool GetKeyDown(WORD ch) {
		if (events.empty() == true) return false;
		const INPUT_RECORD& in = events.front();
		if (in.EventType != KEY_EVENT) return false;
		if (in.Event.KeyEvent.bKeyDown == TRUE) {
			return in.Event.KeyEvent.wVirtualKeyCode == ch;
		}
		return false;
	}

	bool GetLeftMouseDown() {
		if (events.empty() == true) return false;
		const INPUT_RECORD& in = events.front();
		if (in.EventType != MOUSE_EVENT) return false;
		return in.Event.MouseEvent.dwEventFlags == 0
			&& (in.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
	}

	bool GetRightMouseDown() {
		if (events.empty() == true) return false;
		const INPUT_RECORD& in = events.front();
		if (in.EventType != MOUSE_EVENT) return false;
		return in.Event.MouseEvent.dwEventFlags == 0
			&& (in.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED);
	}

	bool GetMouseMove()
	{
		if (events.empty() == true) return false;
		const INPUT_RECORD& in = events.front();
		if (in.EventType != MOUSE_EVENT) return false;
		return in.Event.MouseEvent.dwEventFlags == MOUSE_MOVED
			&& (in.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
			
	} 
	Position GetMousePosition(Position OriginPos)
	{
		//if (GetLeftMouseDownandMove() == false) return OriginPos;
		const INPUT_RECORD& in = events.front();
		return Position(in.Event.MouseEvent.dwMousePosition.X, in.Event.MouseEvent.dwMousePosition.Y);
	}



	void readInputs() {
		DWORD cNumRead;
		DWORD nEvents;

		if (!GetNumberOfConsoleInputEvents(hStdin, &nEvents)) return;
		if (nEvents == 0) return;

		nEvents = min(nEvents, 128);
		ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			nEvents,         // size of read buffer 
			&cNumRead); // number of records read

		for (int i = 0; i < (int)cNumRead; i++) events.push_back(irInBuf[i]);
	}

	void consumeEvent()
	{
		if (events.empty() == true) return;
		events.pop_front();
	}
};

class GameObject {

	string shape;
	Position pos;

	Position parentPos; // your parent's global position in space
	bool dirty; // mark it TRUE if your local position is changed.

protected:
	Screen& screen;
	InputManager& inputManager;

	vector<GameObject *> children;
	GameObject* parent;

	void setParentPos(const Position& parentPos) { this->parentPos = parentPos; }	

public:
	GameObject(int x, int y, const string& shape, GameObject* parent = nullptr)
		: shape(shape), screen(*Screen::getInstance()),
		inputManager(*InputManager::getInstance()),
		pos(x, y), parent(parent), dirty(false)
	{
		setParentPos(parent ? parent->getWorldPos() : Position::zeros);
		if (parent) parent->add(this);
		
		start();
	}

	GameObject(const Position& pos, const string& shape, GameObject* parent = nullptr) 
		: GameObject(pos.x, pos.y, shape, parent) {}

	virtual ~GameObject() {}

	void add(GameObject* child) {
		if (!child) return;
		children.push_back(child);
	}

	void setPos(int x, int y) { setPos(Position{ x, y }); }
	void setPos(const Position& pos) { 
		this->pos.x = pos.x; this->pos.y = pos.y;
		dirty = true;
	}

	Position getPos() const { return pos; }
	Position getWorldPos() const { return parentPos + pos; }
	Position getParentPos() const { return parentPos; }

	const char* getShape() const { return shape.c_str(); }
	void setShape(const string& shape) { this->shape = shape; }

	void setParent(GameObject* parent) {
		this->parent = parent;
		setParentPos(parent ? parent->getWorldPos() : Position::zeros);
		for (auto child : children) child->internalUpdatePos(true);
	}

	virtual void start() {}

	void internalUpdatePos(bool dirty = false) {
		bool inheritedDirty = dirty;
		if (inheritedDirty == false) {
			if (this->dirty == true) inheritedDirty = true;
		} else {
			if (parent) setParentPos(parent->getWorldPos());
		}
		
		for (auto child : children) child->internalUpdatePos(inheritedDirty);
		this->dirty = false;
	}

	void internalUpdate() {
		update();
		for (auto child : children) child->internalUpdate();
	}
	virtual void update() {}

	void internalDraw() { 
		draw();
		for (auto child : children) child->internalDraw();
	}
	virtual void draw() { screen.draw(getWorldPos(), shape.c_str()); }
};

class Panel : public GameObject {
	int width;
	int height;
	string title;
	
public:
	Panel(const string& title, const Position& pos, int width, int height, GameObject* parent) 
		: GameObject(pos, "", parent), 
		width(width), height(height), title(title)
	{}

	void update() override
	{
		Position pos = getPos();
	}

	void draw() override
	{	
		Position pos = getWorldPos();
		screen.drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ width + 2, height + 2 });
		screen.draw(Position{ pos.x + 1, pos.y -1 }, title.c_str());
	}
};
class Button : public GameObject {
	Position size;
	string title;
	bool check;
public:
	Button(const Position& pos, const string& title, const Position& size, GameObject* parent = nullptr)
		: GameObject(pos, "", parent), size(size),title(title),check(false) {}

	~Button() {}
		
	void update() override
	{
		Position pos = getPos();
		Position wpos = getWorldPos();

		if (inputManager.GetLeftMouseDown())
		{
			Position mpos = inputManager.GetMousePosition(pos);
			if (mpos.x > wpos.x&&mpos.x<wpos.x + size.x&&mpos.y>wpos.y&&mpos.y < wpos.y + size.y) {
				check = true;
			}				
		}
	}

	void draw() override 
	{
		Position pos = getWorldPos();
		screen.drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ size.x + 1, size.y + 1 });
		if(check)
			screen.draw(Position{ pos.x + (size.x/2), pos.y + (size.y / 2) }, title.c_str());
	}
};

class Block : public GameObject {
	Position size;
	char* internalShapeData; // it is used only in rotateShape().
	bool rotatable;

	void rotateShape() {
		if (rotatable == false) return;

		string shape = getShape();
		int w = size.x; int h = size.y;
		const char* p = shape.c_str();
		strncpy(internalShapeData, p, w*h);
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++)
				internalShapeData[(w - 1 - x)*h + y] = p[y*w + x];
		setShape(internalShapeData);
		size.x = h; size.y = w;
	}

public:
	Block(const Position& pos, const string& shape, const Position& size, GameObject* parent = nullptr, bool rotatable = true)
		: GameObject(pos, shape, parent), size(size), internalShapeData(new char[size.x*size.y+1]), rotatable(rotatable) {}

	~Block() {
		if (internalShapeData != nullptr) delete[] internalShapeData;
	}

	void update() override
	{
		Position pos = getPos();
		Position wpos = getWorldPos();
		
		if (inputManager.GetKeyDown(VK_UP)) rotateShape();
	
		if (inputManager.GetLeftMouseDown())
		{
			Position mpos = inputManager.GetMousePosition(pos);
			if (mpos.x > wpos.x&&mpos.x<wpos.x + size.x&&mpos.y>wpos.y&&mpos.y < wpos.y + size.y) {
				rotatable = false;
			}
			else
				rotatable = true;
		}

		if (inputManager.GetMouseMove()&&!rotatable)
		{			
			setPos(inputManager.GetMousePosition(pos) - getParentPos());
		}

	}

	void draw() override
	{
		Position pos = getWorldPos();
		screen.drawShape(pos, size, getShape());
	}
};

class Text : public GameObject {

public:
	Text(const Position& pos, const string& message, GameObject* parent)
		: GameObject(pos, message.c_str(), parent)
	{}

	void update() override
	{
		Position pos = getPos();

	}	
};

class TextInput : public GameObject {
	int value;

public:
	TextInput(const Position& pos, int data, GameObject* parent)
		: GameObject(pos, "", parent), value(data)
	{}

	void update() override
	{
		Position pos = getPos();
		//if (inputManager.GetMouseMove())
		//{
		//	setPos(inputManager.GetMousePosition(pos) - getParentPos());
		//}
		//if (inputManager.GetLeftMouseDown()) setPos(pos + Position::left);
		//if (inputManager.GetRightMouseDown()) setPos(pos + Position::right);
	}

	void draw() override
	{
		static char buffer[10];
		sprintf(buffer, "%3d\0", value);
		Position pos = getWorldPos();
		screen.draw(pos, buffer);
	}

	void setValue(int value) { this->value = value; }
};

InputManager* InputManager::instance = nullptr;

int main()
{
	Screen& screen = *Screen::getInstance();
	InputManager& inputManager = *InputManager::getInstance();
	vector<GameObject*> scene;	

	auto panel = new Panel{ "", Position{3,3}, 10, 20, nullptr };
	new Block{ Position{4,0}, "\xdb  \xdb\xdb\xdb  \xdb", Position{ 3, 3}, panel };
	//new Block{ Position{10,0}, "\xdb\xdb \xdb\xdb\xdb", Position{ 2, 3},  panel };
	new Button{ Position{10,0}, "X", Position{ 6, 3},  panel };

	auto nextPanel = new Panel{ " Next", Position{20, 3}, 10, 5, nullptr };
	new Block{ Position{5, 1}, "\xdb \xdb \xdb\xdb", Position{ 2, 3 }, nextPanel, false };

	auto scorePanel = new Panel{ " Score", Position{20, 19}, 10, 4, nullptr };
	int value = 0;
	auto score = new TextInput{ Position{4, 2}, value, scorePanel };

	scene.push_back(panel);
	scene.push_back(nextPanel);
	scene.push_back(scorePanel);

	while (true)
	{
		screen.clear();

		inputManager.readInputs();

		if (inputManager.GetKeyDown(VK_ESCAPE))
		{
			auto overPanel = new Panel{ "", Position{1, 1}, 50, 26, nullptr };
			for (int i = 0; i < 26; i++)
				new Text{ Position{0, i}, "                                           ", overPanel };
			new Button{ Position{31,0}, "-", Position{ 6, 3},  overPanel };
			new Button{ Position{38,0}, "\xdb\xdb", Position{ 6, 3},  overPanel };
			new Button{ Position{45,0}, "X", Position{ 6, 3},  overPanel };
			scene.push_back(overPanel);
		}

		if (inputManager.GetKeyDown(VK_SPACE)) {
			value++;
			score->setValue(value);
		}

		for (auto object : scene) object->internalUpdate();
		for (auto object : scene) object->internalUpdatePos(false);
		for (auto object : scene) object->internalDraw();

		screen.render();

		inputManager.consumeEvent();
		
		Sleep(100);
	}
	printf("\nTerminated Successfully.\n");

	return 0;
}

