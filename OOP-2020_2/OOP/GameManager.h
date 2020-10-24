#pragma once

#include <vector>
using namespace std;

class GameObject;
class InputManager;
class GameManager
{
private:
	//Singleton
	GameManager();

public:
	static GameManager* getInstance()
	{
		if (!instance)
			instance = new GameManager();
		return instance;
	}

	~GameManager();

	void update();
	void start();
	void draw();

private:
	void drawTable();
	void CreateBlock();

private:
	static GameManager* instance;
	vector<GameObject*> scene;
	InputManager& inputManager;
	GameObject* gameTable;
	GameObject*	panel;
	GameObject*	nextPanel;
	GameObject*	scorePanel;
	GameObject*	score;
	GameObject* block;
	GameObject* nextBlock;

	int randomNum;
	int value = 0;

};

