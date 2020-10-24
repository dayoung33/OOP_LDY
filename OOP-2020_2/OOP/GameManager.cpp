#include "GameManager.h"
#include "Utils.h"
#include "InputManager.h"
#include "Block.h"
#include "Panel.h"
#include "TextInput.h"

#include <time.h>
#include <iostream>

GameManager* GameManager::instance = nullptr;


GameManager::GameManager()
	:inputManager(*InputManager::getInstance())
{
	gameTable = 0;
	panel = 0;
	nextPanel = 0;
	scorePanel = 0;
	score = 0;
	block = 0;
	nextBlock = 0;

}

GameManager::~GameManager()
{
}

void GameManager::start()
{
	srand(unsigned int(time(0)));
	randomNum = rand() % 5;

	
	panel = new Panel{ "", Position{3,3}, 10, 20, nullptr };
	nextPanel = new Panel{ " Next", Position{20, 3}, 10, 5, nullptr };
	
	
	gameTable =  new Panel{ "", Position{3,3}, 10, 20, nullptr };
	CreateBlock();
	scorePanel = new Panel{ " Score", Position{20, 19}, 10, 4, nullptr };
	score = new TextInput{ Position{4, 2}, value, scorePanel };

	scene.push_back(panel);
	scene.push_back(nextPanel);
	scene.push_back(scorePanel);
}

void GameManager::update()
{
	if (inputManager.getKeyDown(VK_ESCAPE))
	{
		CreateBlock();
	}

	if (inputManager.getKeyDown(VK_SPACE)) {
		value++;
		dynamic_cast<TextInput*>(score)->setValue(value);
	}

	for (auto object : scene) object->internalUpdate();
	for (auto object : scene) object->internalUpdatePos(false);
}

void GameManager::draw()
{
	for (auto object : scene) object->internalDraw();
}

void GameManager::drawTable()
{
	const char* shape = block->getShape();
	int sx = dynamic_cast<Block*>(block)->getSize().x;
	int sy = dynamic_cast<Block*>(block)->getSize().y;
	for (int h = 0; h < sy; h++)
	{
		for (int w = 0; w < sx; w++)
		{
			if(shape[h*sx+w]!=' ')
				new Block{ Position{block->getPos().x + w ,block->getPos().y + h}, "\xdb", Position{ 1, 1}, gameTable };
		}
	}
}

void GameManager::CreateBlock()
{
	if (block) {
		drawTable();
		delete block;
		block = nullptr;
	}
	if (nextBlock) {
		delete nextBlock;
		nextBlock = nullptr;
	}
	panel->del();
	nextPanel->del();
	switch (randomNum)
	{
	case 0:
		block = new Block{ Position{4,0}, "\xdb \xdb\xdb \xdb", Position{ 2, 3}, panel }; //ぁい
		break;
	case 1:
		block = new Block{ Position{4,0}, "   \xdb   \xdb   \xdb   \xdb", Position{ 4, 4},  panel }; //----
		break;
	case 2:
		block = new Block{ Position{4,0}, "\xdb\xdb\xdb\xdb", Position{ 2, 2},  panel }; //け
		break;
	case 3:
		block = new Block{ Position{4,0}, "\xdb  \xdb\xdb\xdb", Position{ 3, 2},  panel }; //い
		break;
	case 4:
		block = new Block{ Position{4,0}, " \xdb \xdb\xdb\xdb", Position{ 3, 2},  panel }; //で
		break;
	default:
		break;
	}

	int nextNum = rand() % 5;

	switch (nextNum)
	{
	case 0:
		nextBlock = new Block{ Position{5,1}, "\xdb \xdb\xdb \xdb", Position{ 2, 3}, nextPanel, false }; //ぁい
		break;
	case 1:
		nextBlock = new Block{ Position{3,1}, "   \xdb   \xdb   \xdb   \xdb", Position{ 4, 4}, nextPanel, false }; //----
		break;
	case 2:
		nextBlock = new Block{ Position{5,1}, "\xdb\xdb\xdb\xdb", Position{ 2, 2}, nextPanel, false }; //け
		break;
	case 3:
		nextBlock = new Block{ Position{5,1}, "\xdb  \xdb\xdb\xdb", Position{ 3, 2}, nextPanel, false }; //い
		break;
	case 4:
		nextBlock = new Block{ Position{5,1}, " \xdb \xdb\xdb\xdb", Position{ 3, 2}, nextPanel, false }; //で
		break;
	default:
		break;
	}

	randomNum = nextNum;	

}
