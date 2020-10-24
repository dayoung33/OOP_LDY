#include "Table.h"
#include "InputManager.h"
#include "Screen.h"
#include "Block.h"

Table* Table::instance = nullptr;

enum eState { EMPTY, GLASS, WALL, ACTIVE, INACTIVE };	//0,1,2,3...

Table::Table()
	:screen(*Screen::getInstance()),
	inputManager(*InputManager::getInstance())
{
	blockList.push_back(new Block);
	m_tableWidth = screen.getWidth();
	m_tableHeight = screen.getHeight();
	table.reserve(m_tableWidth * m_tableHeight); //저장할 공간 예약

		// 모든 원소 0으로 초기화
	for (int i = 0; i < m_tableHeight; i++) {
		vector<int> temp;
		for (int j = 0; j < m_tableWidth; j++) {
			temp.push_back(EMPTY);
		}
		table.push_back(temp);
	}
}

Table::~Table()
{
	for (auto list : blockList)
	{
		if(!list)
			delete list;
	}
	blockList.clear();
	//delete block;
}

void Table::start()
{
	for (int i = 0; i < m_tableHeight; i++) 	
		for (int j = 0; j < m_tableWidth; j++) 
			table[i][j] = EMPTY;

	// 벽 세팅
	for (int j = 0; j < m_tableHeight - 1; j++) { 	 //left		
		table[0][j] = WALL;	//벽이 2칸이라 2개
		table[1][j] = GLASS; //그림그리기용 보이지 않는 벽
	}

	for (int j = 0; j < m_tableHeight - 1; j++) { 	//right
		table[m_tableWidth - 2][j] = WALL;
		table[m_tableWidth - 1][j] = GLASS;
	}

	for (int j = 0; j < m_tableWidth; j++) 	//bottom
		if (j % 2 == 0)
			table[j][m_tableHeight - 1] = WALL;
		else
			table[j][m_tableHeight - 1] = GLASS;
}

void Table::update()
{
	if (combo % 3 == 0) {		
		for (auto block : blockList)			
			block->upSpeed(level);
	}

	if (!blockList.empty()) {
		for (auto block : blockList) {

			block->update();

			if (checkCollision() == -1 && block->getActive()) {
			
				table[block->getPos().x][block->getPos().y] = ACTIVE;
				table[block->getPos().x + 1][block->getPos().y] = GLASS;		
			}
			else
			{
				table[block->getPos().x][block->getPos().y] = INACTIVE;
				table[block->getPos().x + 1][block->getPos().y] = GLASS;
			}		
		}
	}

	//한줄 다 채우면 지우기
	for (int i = 4; i < m_tableHeight - 1; i++) {
		if (9 == checkCombo(i))
		{
			combo++;			
			score += combo * level;
			if(combo%3 == 0)
				level++;
			for (int j = 2; j < m_tableWidth - 3; j++)
				table[j][i] = EMPTY;
			for (auto iter = blockList.begin(); iter != blockList.end();)
			{
				if ((*iter)->getInactivePos() == i)			 
					iter = blockList.erase(iter);
				else {
					(*iter)->setPos((*iter)->getPos().x, (*iter)->getPos().y + 1);
					(*iter)->setInactivePos((*iter)->getInactivePos() + 1);
					iter++;
				}
			}
		}
	}	

	for (int j = 2; j < m_tableWidth - 4; j++) {
		if (table[j][4] == INACTIVE) {
			gameOver = true;
		}
	}
}

void Table::draw()
{
	for (int i = 0; i < m_tableHeight; i++) {
		for (int j = 0; j < m_tableWidth; j++) {
			switch (table[i][j])
			{
			case EMPTY:
				screen.draw(i, j, ' ');
				if(j==4)
					screen.draw(i, j, '-');
				break;
			case GLASS:
				break;
			case WALL:
				screen.draw(i, j, "▦");
				break;
			case ACTIVE:
				screen.draw(i, j, "■");
				break;
			case INACTIVE:
				screen.draw(i, j, "□");
				break;
			default:
				break;
			}
		}		
	}
}

int Table::checkCombo(int lineNum)
{
	int cnt = 0;
	if (!blockList.empty()) {
		for (auto block : blockList) {
			if (block->getInactivePos() == lineNum)
				cnt++;
		}
	}
	return cnt;
}

int Table::checkCollision()
{
	Block* temp = nullptr;

	if (!blockList.empty()) {
		for (auto block : blockList)
		{
			if (block->getActive())
				temp = block;
		}
	}
	if (temp == nullptr)
		return 0;

	int xpos = temp->getPos().x;
	int ypos = temp->getPos().y;

	if (table[xpos][ypos + 1] == EMPTY)
		return -1;
	else {	//WALL,GLASS,ACTIVE,INACTIVE가 밑에 존재하면
		temp->setActive(false);
		temp->setInactivePos(ypos);
		blockList.push_back(new Block);
		return ypos;
	}
	
}

int Table::getFallPos(int x)
{
	for (int i = 5; i < m_tableHeight - 1; i++) {
		if (table[x][i] == INACTIVE || table[x][i] == GLASS)
			return i - 2;
	}
	return m_tableHeight - 3;
}




