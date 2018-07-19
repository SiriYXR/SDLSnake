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
	bool isEscape();

private:
	void mouseEvent();
	void keyEvent();

	void rend_background();

private:
	SIRI_Window *win;
	SDL_Event events;

	SIRI_Button* m_starGameButton;
	SIRI_Button* m_aboutUsButton;

	bool isover;
	bool isescape;
};

