#include "GameTable.h"
#include "Panel.h"
#include "Screen.h"

enum eState { EMPTY, BLOCK, WALL };

GameTable::GameTable(const Position & pos, int width, int height, GameObject * parent)
	:GameObject(pos, "", parent), width(width+1), height(height+1),gameover(false)
{
	table.reserve(this->width * this->height); //저장할 공간 예약

	// 모든 원소 0으로 초기화
	for (int i = 0; i <this->width; i++) {
		vector<int> temp;
		for (int j = 0; j <this->height ; j++) {
			temp.push_back(EMPTY); 
		}
		table.push_back(temp);
	}
	for (int i = 0; i < this->width; i++) 
		for (int j = 0; j < this->height; j++) 
			table[i][j] = EMPTY;
}

void GameTable::update()
{
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			table[i][j] = EMPTY;

	for (auto block : children)
	{
		table[block->getPos().x][block->getPos().y] = BLOCK;
	}

	for (int i = 0; i < this->width; i++)
	{
		if (table[i][4] == BLOCK)
			gameover = true;
	}

	int cnt = 0;
	for (int j = this->height - 1; j >= 0; j--) {
		for (int i = 0; i < this->width; i++)
		{
			if (table[i][j] == BLOCK)
				cnt++;
			else {
				break;
			}
		}
		if (cnt == width)
		{
			deleteLine(j);
		}
		cnt = 0;
	}			
}

void GameTable::draw()
{
	Position pos = getWorldPos();
	screen.draw(Position{ pos.x,pos.y+4 }, "-----------");
}

void GameTable::addBlock(int x, int y)
{
	table[x][y] = BLOCK;
}

void GameTable::deleteLine(int y)
{
	for (int i = 0; i < width; i++) 
		table[i][y] = EMPTY;
	for (auto iter = children.begin(); iter != children.end();)
	{
		if ((*iter)->getPos().y == y)
			iter = children.erase(iter);
		else if((*iter)->getPos().y > y)
			iter++;
		else {
			(*iter)->setPos((*iter)->getPos().x, (*iter)->getPos().y + 1);
			iter++;
		}
	}
	
}
int GameTable::getState(int x, int y)
{
	return table[x][y];
}

void GameTable::restart()
{
	for (auto block : children)
	{
		delete block;
		block = nullptr;
	}
	children.clear();

	table.reserve(this->width * this->height);

	// 모든 원소 0으로 초기화
	for (int i = 0; i < this->width; i++) {
		vector<int> temp;
		for (int j = 0; j < this->height; j++) {
			temp.push_back(EMPTY);
		}
		table.push_back(temp);
	}
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			table[i][j] = EMPTY;	
	
	gameover = false;
}
