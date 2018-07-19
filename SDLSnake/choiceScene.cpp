#include "choiceScene.h"


choiceScene::choiceScene(SIRI_Window * win) :win(win)
{
	m_singlGameButton = new SIRI_Button(win, SIRI_Rect(120, 410, win->mImage->switch_oneplayer), win->mImage->switch_oneplayer);
	m_doubleGameButton = new SIRI_Button(win, SIRI_Rect(440, 410, win->mImage->switch_twoplayer), win->mImage->switch_twoplayer);

	m_dir.setX(50);
	m_dir.setY(415);

	isover = false;
	isescape = false;
}

choiceScene::~choiceScene()
{
}

void choiceScene::event()
{
	while (SDL_PollEvent(&events))
	{
		//If user closes the window
		if (events.type == SDL_QUIT)
		{
			isover = true;
			isescape = true;
			return;
		}

		if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseEvent();
		}

		if (events.type == SDL_MOUSEMOTION)
		{
			if (m_singlGameButton->isOn())
				m_dir.setX(50);
			if (m_doubleGameButton->isOn())
				m_dir.setX(370);
		}

		if (events.type == SDL_KEYDOWN)
		{
			keyEvent();
		}

		m_singlGameButton->event(&events);
		m_doubleGameButton->event(&events);
	}
}

void choiceScene::update()
{
}

void choiceScene::rend()
{
	win->Clear();

	rend_background();

	rend_dir();

	m_singlGameButton->render();
	m_doubleGameButton->render();

	win->Present();
}

bool choiceScene::isOver()
{
	return isover;
}

bool choiceScene::isEscape()
{
	return isescape;
}

void choiceScene::mouseEvent()
{
	int x, y;
	x = events.motion.x;
	y = events.motion.y;

	if (events.button.button == SDL_BUTTON_LEFT) {
		
		if (m_singlGameButton->isOn()) {
			win->mMusic->click->play();
			if (gameloop(win, 1)) {
				isover = true;
				isescape = true;
			}
		}

		if (m_doubleGameButton->isOn()) {
			win->mMusic->click->play();
			if (gameloop(win, 2)) {
				isover = true;
				isescape = true;
			}
		}
	}
}

void choiceScene::keyEvent()
{
	switch (events.key.keysym.sym)
	{
	case SDLK_a:
	case SDLK_LEFT:
		if (m_dir.getX() != 50)
			m_dir.setX(50);
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		if (m_dir.getX() != 370)
			m_dir.setX(370);
		break;
	case SDLK_SPACE:
	case SDLK_KP_ENTER:
	case SDLK_RETURN:
		if (m_dir.getX() == 50) {
			win->mMusic->click->play();
			if (gameloop(win, 1)) {
				isover = true;
				isescape = true;
			}
		}
		else if (m_dir.getX() == 370) {
			win->mMusic->click->play();
			if (gameloop(win, 2)) {
				isover = true;
				isescape = true;
			}
		}
		break;
	case SDLK_ESCAPE:
		win->mMusic->click->play();
		isover = true;
		isescape = false;
		break;
	}
}

void choiceScene::rend_background()
{
	win->Draw(win->mImage->intogame, 0, 0);
}

void choiceScene::rend_dir()
{
	win->Draw(win->mImage->director, m_dir.getX(), m_dir.getY());
}
