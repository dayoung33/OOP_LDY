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
	block = new Block;
	m_tableWidth = screen.getWidth();
	m_tableHeight = screen.getHeight();
	table.reserve(m_tableWidth * m_tableHeight); //������ ���� ����
		// ��� ���� 0���� �ʱ�ȭ
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
	delete block;
}

void Table::start()
{
	for (int i = 0; i < m_tableHeight; i++) 	
		for (int j = 0; j < m_tableWidth; j++) 
			table[i][j] = EMPTY;

	// �� ����
	for (int j = 0; j < m_tableHeight - 1; j++) { 	 //left		
		table[0][j] = WALL;	//���� 2ĭ�̶� 2��
		table[1][j] = GLASS; //�׸��׸���� ������ �ʴ� ��
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
	//��üũ,�޺��߰�,�����߰�,������
	
	block->update();
	table[block->getPos().x][block->getPos().y] = ACTIVE;
	table[block->getPos().x+1][block->getPos().y] = GLASS;

}

void Table::draw()
{
	for (int i = 0; i < m_tableHeight; i++) {
		for (int j = 0; j < m_tableWidth; j++) {
			switch (table[i][j])
			{
			case EMPTY:
				screen.draw(i, j, ' ');
				break;
			case GLASS:
				break;
			case WALL:
				screen.draw(i, j, "��");
				break;
			case ACTIVE:
				screen.draw(i, j, "��");
				break;
			case INACTIVE:
				screen.draw(i, j, "��");
				break;
			default:
				break;
			}
		}		
	}
}




