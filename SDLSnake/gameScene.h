#pragma once
#include "function.h"
#include "Snake.h"

//游戏状态
enum State
{
	INIT,
	RUNNING,
	PAUSE,
	DEAD
};

//死亡信息
enum DeadFor
{
	NOTHING,
	P1WIN,
	P2WIN,
	NEWSCORE
};

class gameScene
{
public:
	gameScene(SIRI_Window *win,int mod);
	~gameScene();

	void event();
	void update();
	void rend();
	bool isOver();
	bool isEscape();

private:
	void init();//初始化游戏

	void updateButton();
	void updateSnake();//更新蛇的状态
	void updateCreatFood();//创建食物
	void updateEatFood();//食物碰撞检测

	void rend_background();
	void rend_button();
	void rendSnake();//渲染蛇
	void rendDead();//渲染死亡界面
	void rendFood();//渲染食物
	void rendPlayerName();//双人模式下渲染玩家名
	void rendPause();//渲染暂停界面

	void mouseEvent();
	void keyEvent();
	void buttonEvent(SDL_Event& events);

	bool isSnakeDead();//判定游戏是否结束
	bool isOutMap(Snake* snake);//判定是否超出地图边界
	bool isEatSelf(Snake* snake);//判定是否吃到自己
	bool isEatOthers(Snake* s1, Snake* s2);//是否吃到别人
private:
	SIRI_Window *m_win;
	SDL_Event events;

	State m_state;//游戏状态
	DeadFor m_deadFor;//死亡原因

	SIRI_Button* m_muteButton;
	SIRI_Button* m_unmuteButton;
	SIRI_Button* m_startButton;
	SIRI_Button* m_continueButton;
	SIRI_Button* m_pauseButton;
	SIRI_Button* m_backButton;

	Snake* m_snake[2];//蛇
	list<SIRI_Point> m_food;//食物链表

	int m_mod;//游戏模式
	int m_score[2];//玩家分数
	int m_highestScore;//历史最高分

	bool ismute;//是否静音
	bool isover;
	bool isescape;
};

