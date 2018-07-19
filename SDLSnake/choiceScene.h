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
	void rend_dir();

private:
	SIRI_Window *win;
	SDL_Event events;

	SIRI_Button* m_singlGameButton;
	SIRI_Button* m_doubleGameButton;

	SIRI_Point m_dir;

	bool isover;
	bool isescape;
};

