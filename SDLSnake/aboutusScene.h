#pragma once
#include "function.h"

class aboutusScene
{
public:
	aboutusScene(SIRI_Window *win);
	~aboutusScene();

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

	bool isover;
	bool isescape;
};

