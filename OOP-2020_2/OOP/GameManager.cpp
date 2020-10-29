#include "GameManager.h"
#include "Utils.h"
#include "InputManager.h"
#include "Block.h"
#include "Panel.h"
#include "TextInput.h"
#include "Text.h"
#include "GameTable.h"
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
	overPanelinit = false;
	restartInit = false;
	pausePanelInit = false; 
	replayInit = false;
	isPause = false;
}

GameManager::~GameManager()
{
}

void GameManager::start()
{
	srand(unsigned int(time(0)));
	randomNum = rand() % 5;

	gameTable =  new GameTable{ Position{3,3}, 10, 20, nullptr };	
	panel = new Panel{ "", Position{3,3}, 10, 20, nullptr };
	nextPanel = new Panel{ " Next", Position{20, 3}, 10, 5, nullptr };
		
	createBlock();
	scorePanel = new Panel{ " Score", Position{20, 19}, 10, 4, nullptr };
	score = new TextInput{ Position{4, 2}, value, scorePanel };
	
	scene.push_back(gameTable);
	scene.push_back(panel);
	scene.push_back(nextPanel);
	scene.push_back(scorePanel);
}

void GameManager::update()
{
	if (dynamic_cast<GameTable*>(gameTable)->getOver()) {
		createGameOverPanel();
		if (inputManager.getKeyDown(VK_F1))
			restart();		
	}
	if (inputManager.getKeyDown(VK_ESCAPE))
	{
		isPause = true;
		creatPausePanel();
	}
	if (isPause)
	{
		if (inputManager.getKeyDown(VK_F1))
			replay();
		if (inputManager.getKeyDown('Q'))
			exit(0);
	}
	
	if (!dynamic_cast<Block*>(block)->getRotatable())
		createBlock();

	for (auto object : scene) object->internalUpdate();
	for (auto object : scene) object->internalUpdatePos(false);
	
}

void GameManager::draw()
{
	for (auto object : scene) object->internalDraw();
}

bool GameManager::getOver()
{
	return dynamic_cast<GameTable*>(gameTable)->getOver();
}

void GameManager::drawTable()
{
	value += rand() % 100 + 1;
	dynamic_cast<TextInput*>(score)->setValue(value);
	const char* shape = block->getShape();
	int sx = dynamic_cast<Block*>(block)->getSize().x;
	int sy = dynamic_cast<Block*>(block)->getSize().y;
	int px = block->getPos().x;
	int py = block->getPos().y;

	for (int h = 0; h < sy; h++)
	{
		for (int w = 0; w < sx; w++)
		{
			if (shape[h*sx + w] != ' ') {
				new Block{ Position{px+ w ,py+ h}, "\xdb", Position{ 1, 1}, gameTable, false };
				dynamic_cast<GameTable*>(gameTable)->addBlock(px + w, py + h);
			}
		}
	}
}

void GameManager::createBlock()
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
		dynamic_cast<Block*>(block)->setGametable(gameTable);
		break;
	case 1:
		block = new Block{ Position{4,0}, "   \xdb   \xdb   \xdb   \xdb", Position{ 4, 4},  panel }; //----
		dynamic_cast<Block*>(block)->setGametable(gameTable);
		break;
	case 2:
		block = new Block{ Position{4,0}, "\xdb\xdb\xdb\xdb", Position{ 2, 2},  panel }; //け
		dynamic_cast<Block*>(block)->setGametable(gameTable);
		break;
	case 3:
		block = new Block{ Position{4,0}, "\xdb  \xdb\xdb\xdb", Position{ 3, 2},  panel }; //い
		dynamic_cast<Block*>(block)->setGametable(gameTable);
		break;
	case 4:
		block = new Block{ Position{4,0}, " \xdb \xdb\xdb\xdb", Position{ 3, 2},  panel }; //で
		dynamic_cast<Block*>(block)->setGametable(gameTable);
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

void GameManager::createGameOverPanel()
{
	if (!overPanelinit) {
		dynamic_cast<Block*>(block)->setPause(true);
		auto overPanel = new Panel{ "", Position{8, 9}, 15, 7, nullptr };
		for (int i = 0; i < 8; i++)
			new Text{ Position{0, i}, "                ", overPanel };
		new Text{ Position{4, 3}, "GameOver!", overPanel };
		new Text{ Position{2, 4}, "restart : F1", overPanel };
		scene.push_back(overPanel);
		overPanelinit = true;
		restartInit = false;
	}
}

void GameManager::restart()
{
	if (!restartInit)
	{
		dynamic_cast<GameTable*>(gameTable)->restart();
		scene.pop_back();
		dynamic_cast<Block*>(block)->setPause(false);
		value = 0;
		dynamic_cast<TextInput*>(score)->setValue(value);
		restartInit = true;
		overPanelinit = false;
	}
}

void GameManager::creatPausePanel()
{
	if (!pausePanelInit) {
		dynamic_cast<Block*>(block)->setPause(true);
		auto pausePanel = new Panel{ "", Position{8, 9}, 15, 7, nullptr };
		for (int i = 0; i < 8; i++)
			new Text{ Position{0, i}, "                ", pausePanel };
		new Text{ Position{2, 3}, "System Pause", pausePanel };
		new Text{ Position{3, 4}, "resume : F1", pausePanel };
		new Text{ Position{4, 5}, "Exit : Q", pausePanel };

		scene.push_back(pausePanel);
		pausePanelInit = true;
		replayInit = false;
	}
}

void GameManager::replay()
{
	if (!replayInit)
	{
		scene.pop_back();
		dynamic_cast<Block*>(block)->setPause(false);
		replayInit = true;
		pausePanelInit = false;
		isPause = false;
	}
}
