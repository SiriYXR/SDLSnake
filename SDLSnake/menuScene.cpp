#include "menuScene.h"

menuScene::menuScene(SIRI_Window *win):win(win)
{
	//实例化按钮对象
	m_starGameButton = new SIRI_Button(win, SIRI_Rect(250,410, win->mImage->switch_startgame), win->mImage->switch_startgame);
	m_aboutUsButton = new SIRI_Button(win, SIRI_Rect( 550, 410,win->mImage->aboutus_button ),win->mImage->aboutus_button);

	isover = false;
	isescape = false;
}


menuScene::~menuScene()
{
}

void menuScene::event()
{
	while (SDL_PollEvent(&events))
	{
		//If user closes the window
		if (events.type == SDL_QUIT)//窗口事件
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

		m_starGameButton->event(&events);
		m_aboutUsButton->event(&events);

	}
}

void menuScene::update()
{
}

void menuScene::rend()
{
	win->Clear();//清空窗口中的图像

	rend_background();

	//渲染按钮
	m_starGameButton->render();
	m_aboutUsButton->render();

	win->Present();//显示窗口中的图像
}

bool menuScene::isOver()
{
	return isover;
}

bool menuScene::isEscape()
{
	return isescape;
}

void menuScene::mouseEvent()
{
	int x, y;
	x = events.motion.x;
	y = events.motion.y;

	if (events.button.button == SDL_BUTTON_LEFT) {
			if (m_starGameButton->isOn())
			{
				win->mMusic->click->play();//播放按钮音效
				if (choiceloop(win)) {//进入模式选择场景
					isover = true;
					isescape = true;
				}
			}

			if (m_aboutUsButton->isOn())
			{
				win->mMusic->click->play();
				if (aboutusloop(win)) {//进入开发人员名单场景
					isover = true;
					isescape = true;
				}
				
			}
		
	}
}

void menuScene::keyEvent()
{
	switch (events.key.keysym.sym)
	{
	case SDLK_SPACE:
	case SDLK_KP_ENTER:
	case SDLK_RETURN:
		win->mMusic->click->play();
		if (choiceloop(win)) {
			isover = true;
			isescape = true;
		}
		break;
	case SDLK_ESCAPE:
		win->mMusic->click->play();
		isover = true;
		isescape = true;
		break;
	}
}

void menuScene::rend_background()
{
	win->Draw(win->mImage->intogame, 0, 0);
	
}

