#pragma once

#include "SIRI_GUI.h"

#include <list>

using namespace siri;
using namespace std;

//蛇身
struct Node
{
	int x, y;
	int direction;
	struct Node* next;
	struct Node* prev;
};

//方向
struct Direction
{
	int x, y;
};

const Direction Dir[4] = {{ -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };//方向数组

#define SpeedMax 5//最大速度

class Snake
{
public:
	Snake(SIRI_Window * win,SIRI_Point point,int direction);
	~Snake();

	void update();
	void render();

	void putKey(int key);//设置操作指令
	SIRI_Point& getHeadPoint();//获取当前蛇头位置
	SIRI_Point& getNextHeadPoint();//获取蛇头预计到达位置
	void grow();//从尾部生长一个结点
	bool isEatSelf();
	bool isOnBody(SIRI_Point point);//判定是否与自身结点重合
	bool isCanMove();//判定是否可以移动
	
	void rollBack();//倒退一步（只要死亡时
	void speedUp();//加速
	void setAccelerate(bool iscan);//临时加速
private:
	//链表操作
	void pushBack();
	bool popFront();
	int getLength();
	bool isEmpty();
	void clear();

	void updateCount();//更新计数器
	void updateMove();//移动
	void updateHeadDir();//更新蛇头方向
	void updateHeadPoint();//更新蛇头位置

private:
	SIRI_Window * m_win;

	Node* m_nodeHead;//蛇头指针
	Node* m_nodeTail;//蛇尾指针

	SIRI_Point m_headPoint;//蛇头位置
	int m_headDir;//蛇头的方向
	list<int> m_key;//操作指令链表
	int m_length;//蛇长
	double m_speed;//速度
	int m_accelerate;//加速计时器

	double m_count;//计数器

	bool m_isCanAccelerate;//是否处于加速状态
};

