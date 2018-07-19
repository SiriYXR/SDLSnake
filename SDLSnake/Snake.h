#pragma once

#include "SIRI_GUI.h"

#include <list>

using namespace siri;
using namespace std;

//����
struct Node
{
	int x, y;
	int direction;
	struct Node* next;
	struct Node* prev;
};

//����
struct Direction
{
	int x, y;
};

const Direction Dir[4] = {{ -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };//��������

#define SpeedMax 5//����ٶ�

class Snake
{
public:
	Snake(SIRI_Window * win,SIRI_Point point,int direction);
	~Snake();

	void update();
	void render();

	void putKey(int key);//���ò���ָ��
	SIRI_Point& getHeadPoint();//��ȡ��ǰ��ͷλ��
	SIRI_Point& getNextHeadPoint();//��ȡ��ͷԤ�Ƶ���λ��
	void grow();//��β������һ�����
	bool isEatSelf();
	bool isOnBody(SIRI_Point point);//�ж��Ƿ����������غ�
	bool isCanMove();//�ж��Ƿ�����ƶ�
	
	void rollBack();//����һ����ֻҪ����ʱ
	void speedUp();//����
	void setAccelerate(bool iscan);//��ʱ����
private:
	//�������
	void pushBack();
	bool popFront();
	int getLength();
	bool isEmpty();
	void clear();

	void updateCount();//���¼�����
	void updateMove();//�ƶ�
	void updateHeadDir();//������ͷ����
	void updateHeadPoint();//������ͷλ��

private:
	SIRI_Window * m_win;

	Node* m_nodeHead;//��ͷָ��
	Node* m_nodeTail;//��βָ��

	SIRI_Point m_headPoint;//��ͷλ��
	int m_headDir;//��ͷ�ķ���
	list<int> m_key;//����ָ������
	int m_length;//�߳�
	double m_speed;//�ٶ�
	int m_accelerate;//���ټ�ʱ��

	double m_count;//������

	bool m_isCanAccelerate;//�Ƿ��ڼ���״̬
};

