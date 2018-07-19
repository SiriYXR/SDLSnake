#pragma once

#include "SIRI_GUI.h"

#include <list>

using namespace siri;
using namespace std;

struct Node
{
	int x, y;
	int direction;
	struct Node* next;
	struct Node* prev;
};

struct Direction
{
	int x, y;
};

const Direction Dir[4] = {{ -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };

#define SpeedMax 5

class Snake
{
public:
	Snake(SIRI_Window * win,SIRI_Point point,int direction);
	~Snake();

	void update();
	void render();

	void putKey(int key);
	SIRI_Point& getHeadPoint();
	SIRI_Point& getNextHeadPoint();
	void grow();
	bool isEatSelf();
	bool isOnBody(SIRI_Point point);
	bool isCanMove();

	void rollBack();
	void speedUp();
	void setAccelerate(bool iscan);
private:
	void pushBack();
	bool popFront();
	int getLength();
	bool isEmpty();
	void clear();

	void updateCount();
	void updateMove();
	void updateHeadDir();
	void updateHeadPoint();

private:
	SIRI_Window * m_win;

	Node* m_nodeHead;
	Node* m_nodeTail;

	SIRI_Point m_headPoint;
	int m_headDir;
	list<int> m_key;
	int m_length;
	double m_speed;
	int m_accelerate;

	double m_count;

	bool m_isCanAccelerate;
};

