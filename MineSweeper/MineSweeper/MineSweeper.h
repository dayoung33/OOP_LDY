#pragma once
class Screen;
class MineSweeper
{
private:
	//Singleton
	MineSweeper(int width, int height);

public:
	static MineSweeper* GetInstance(int width, int height)
	{
		if (!instance)
			instance = new MineSweeper(width, height);

		return instance;
	}

	~MineSweeper();

public:
	void	InitMine();
	void	SetScreen(Screen* _screen);
	int		GetData(int index);	
	int		GetFindMineNum();
	bool	GetOver();
	bool	GetClear();
	void	CheckMine(int xpos, int ypos, bool check);
	void	GameLoop(int xpos, int ypos);

private:
	void	DoubleCheck(int x, int y);
	void    TripleCheck(int x, int y);
	void	QuadCheck(int x, int y);
	bool	Bomb(int x, int y);
	void	SetMine();
	int		MineNumCheck(int index);
	void	SetNum();

private:
	static MineSweeper* instance;
	Screen* screen;
	int* m_buffer; 

	bool gameover;
	int m_mineCnt;
	int m_foundMine;
	int m_width;
	int m_height;

};

