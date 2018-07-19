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
	bool isEscape();//是否退出程序

private:
	void mouseEvent();//鼠标事件处理
	void keyEvent();//键盘事件处理

	void rend_background();//渲染背景

private:
	SIRI_Window *win;
	SDL_Event events;

	SIRI_Button* m_starGameButton;//开始游戏按钮
	SIRI_Button* m_aboutUsButton;//开发人员名单按钮

	bool isover;
	bool isescape;
};

