#pragma once
#include "function.h"
#include "Snake.h"

enum State
{
	INIT,
	RUNNING,
	PAUSE,
	DEAD
};

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
	void init();

	void updateButton();
	void updateSnake();
	void updateCreatFood();
	void updateEatFood();

	void rend_background();
	void rend_button();
	void rendSnake();
	void rendDead();
	void rendFood();
	void rendPlayerName();
	void rendPause();

	void mouseEvent();
	void keyEvent();
	void buttonEvent(SDL_Event& events);

	bool isSnakeDead();
	bool isOutMap(Snake* snake);
	bool isEatSelf(Snake* snake);
	bool isEatOthers(Snake* s1, Snake* s2);
private:
	SIRI_Window *m_win;
	SDL_Event events;

	State m_state;
	DeadFor m_deadFor;

	SIRI_Button* m_muteButton;
	SIRI_Button* m_unmuteButton;
	SIRI_Button* m_startButton;
	SIRI_Button* m_continueButton;
	SIRI_Button* m_pauseButton;
	SIRI_Button* m_backButton;

	Snake* m_snake[2];
	list<SIRI_Point> m_food;

	int m_mod;
	int m_score[2];
	int m_highestScore;

	bool ismute;
	bool isover;
	bool isescape;
};

