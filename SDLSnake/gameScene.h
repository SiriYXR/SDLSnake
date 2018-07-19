#pragma once
#include "function.h"
#include "Snake.h"

//��Ϸ״̬
enum State
{
	INIT,
	RUNNING,
	PAUSE,
	DEAD
};

//������Ϣ
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
	void init();//��ʼ����Ϸ

	void updateButton();
	void updateSnake();//�����ߵ�״̬
	void updateCreatFood();//����ʳ��
	void updateEatFood();//ʳ����ײ���

	void rend_background();
	void rend_button();
	void rendSnake();//��Ⱦ��
	void rendDead();//��Ⱦ��������
	void rendFood();//��Ⱦʳ��
	void rendPlayerName();//˫��ģʽ����Ⱦ�����
	void rendPause();//��Ⱦ��ͣ����

	void mouseEvent();
	void keyEvent();
	void buttonEvent(SDL_Event& events);

	bool isSnakeDead();//�ж���Ϸ�Ƿ����
	bool isOutMap(Snake* snake);//�ж��Ƿ񳬳���ͼ�߽�
	bool isEatSelf(Snake* snake);//�ж��Ƿ�Ե��Լ�
	bool isEatOthers(Snake* s1, Snake* s2);//�Ƿ�Ե�����
private:
	SIRI_Window *m_win;
	SDL_Event events;

	State m_state;//��Ϸ״̬
	DeadFor m_deadFor;//����ԭ��

	SIRI_Button* m_muteButton;
	SIRI_Button* m_unmuteButton;
	SIRI_Button* m_startButton;
	SIRI_Button* m_continueButton;
	SIRI_Button* m_pauseButton;
	SIRI_Button* m_backButton;

	Snake* m_snake[2];//��
	list<SIRI_Point> m_food;//ʳ������

	int m_mod;//��Ϸģʽ
	int m_score[2];//��ҷ���
	int m_highestScore;//��ʷ��߷�

	bool ismute;//�Ƿ���
	bool isover;
	bool isescape;
};

