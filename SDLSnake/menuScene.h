#pragma once
#include "function.h"

class menuScene
{
public:
	menuScene(SIRI_Window *win);
	~menuScene();

	void event();
	void update();
	void rend();
	bool isOver();
	bool isEscape();//�Ƿ��˳�����

private:
	void mouseEvent();//����¼�����
	void keyEvent();//�����¼�����

	void rend_background();//��Ⱦ����

private:
	SIRI_Window *win;
	SDL_Event events;

	SIRI_Button* m_starGameButton;//��ʼ��Ϸ��ť
	SIRI_Button* m_aboutUsButton;//������Ա������ť

	bool isover;
	bool isescape;
};

