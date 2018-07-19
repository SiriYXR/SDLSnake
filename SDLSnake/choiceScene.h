#pragma once
#include "function.h"

class choiceScene
{
public:
	choiceScene(SIRI_Window *win);
	~choiceScene();

	void event();
	void update();
	void rend();
	bool isOver();
	bool isEscape();

private:
	void mouseEvent();
	void keyEvent();

	void rend_background();
	void rend_dir();//渲染选择光标

private:
	SIRI_Window *win;
	SDL_Event events;

	SIRI_Button* m_singlGameButton;
	SIRI_Button* m_doubleGameButton;

	SIRI_Point m_dir;//光标

	bool isover;
	bool isescape;
};

