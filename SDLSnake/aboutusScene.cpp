#include "aboutusScene.h"


aboutusScene::aboutusScene(SIRI_Window * win) :win(win)
{
	isover = false;
	isescape = false;
}

aboutusScene::~aboutusScene()
{
}

void aboutusScene::event()
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

		if (events.type == SDL_KEYDOWN)
		{
			keyEvent();
		}

	}
}

void aboutusScene::update()
{
}

void aboutusScene::rend()
{
	win->Clear();

	rend_background();

	win->Present();
}

bool aboutusScene::isOver()
{
	return isover;
}

bool aboutusScene::isEscape()
{
	return isescape;
}

void aboutusScene::mouseEvent()
{
	win->mMusic->click->play();
	isover = true;
	isescape = false;
}

void aboutusScene::keyEvent()
{
	win->mMusic->click->play();
	isover = true;
	isescape = false;
}

void aboutusScene::rend_background()
{
	win->Draw(win->mImage->map, 0, 0);
	win->Draw(win->mImage->map, 500-20, 0);
	win->Draw(win->mImage->map, 0, 500-20);
	win->Draw(win->mImage->map, 500-20, 500-20);
	win->Draw(win->mImage->aboutus_interface, 100, 100);
}
