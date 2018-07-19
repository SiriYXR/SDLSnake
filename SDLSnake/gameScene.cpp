#include "gameScene.h"


gameScene::gameScene(SIRI_Window * win, int mod) :m_win(win)
{
	m_mod = mod;

	m_muteButton = new SIRI_Button(m_win, SIRI_Rect(700, 0, m_win->mImage->noVoice), m_win->mImage->noVoice);
	m_unmuteButton = new SIRI_Button(m_win, SIRI_Rect(700, 0, m_win->mImage->isVoice), m_win->mImage->isVoice);
	m_backButton = new SIRI_Button(m_win, SIRI_Rect(750, 0, m_win->mImage->back), m_win->mImage->back);
	m_startButton = new SIRI_Button(m_win, SIRI_Rect(685, 90, m_win->mImage->start), m_win->mImage->start);
	m_continueButton = new SIRI_Button(m_win, SIRI_Rect(685, 90, m_win->mImage->continu), m_win->mImage->continu);
	m_pauseButton = new SIRI_Button(m_win, SIRI_Rect(685, 90, m_win->mImage->pause), m_win->mImage->pause);

	m_state = INIT;
	init();

	ismute = false;
	isover = false;
	isescape = false;
}

gameScene::~gameScene()
{
}

void gameScene::event()
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

		if (events.type == SDL_MOUSEMOTION) {
			buttonEvent(events);
		}
	}
}

void gameScene::update()
{

	init();

	updateSnake();

	updateEatFood();

	updateCreatFood();

	updateButton();
}

void gameScene::rend()
{
	m_win->Clear();

	rend_background();

	rend_button();

	rendFood();

	rendSnake();

	rendPause();

	rendDead();

	m_win->Present();
}

bool gameScene::isOver()
{
	return isover;
}

bool gameScene::isEscape()
{
	return isescape;
}

void gameScene::init()
{
	if (m_state == INIT) {
		m_state = RUNNING;
		m_deadFor = NOTHING;

		m_score[0] = 0;
		m_score[1] = 0;
		m_highestScore = readScore(ScoreFile);

		m_snake[0] = new Snake(m_win, SIRI_Point(200, 280), 0);
		if (m_mod == 1) {
			m_snake[1] = NULL;
		}
		else
		{
			m_snake[1] = new Snake(m_win, SIRI_Point(320, 280), 2);
			m_snake[0]->setAccelerate(false);
			m_snake[1]->setAccelerate(false);
		}

		if (!m_food.empty())
			m_food.pop_front();
		updateCreatFood();
	}
}

void gameScene::updateButton()
{
	if (ismute) {
		m_muteButton->setIsHiden(false);
		m_unmuteButton->setIsHiden(true);
	}
	else {
		m_muteButton->setIsHiden(true);
		m_unmuteButton->setIsHiden(false);
	}

	switch (m_state)
	{
	case RUNNING:
		m_continueButton->setIsHiden(true);
		m_startButton->setIsHiden(true);
		m_pauseButton->setIsHiden(false);
		break;
	case PAUSE:
		m_continueButton->setIsHiden(false);
		m_startButton->setIsHiden(true);
		m_pauseButton->setIsHiden(true);
		break;
	case DEAD:
		m_continueButton->setIsHiden(true);
		m_startButton->setIsHiden(false);
		m_pauseButton->setIsHiden(true);
		break;
	default:
		break;
	}
}

void gameScene::updateSnake()
{
	if (m_state == RUNNING) {
		if (!isSnakeDead()) {
			m_snake[0]->update();
			if (m_mod == 2) {
				m_snake[1]->update();
			}
		}
	}
}

void gameScene::updateCreatFood()
{
	while (m_food.size() < 5) {
		int x = 20 + SIRI_Rand(24) * 20;
		int y = 20 + SIRI_Rand(24) * 20;
		bool flag = true;
		for (int i = 0; i < 2; i++)
			if (m_snake[i])
				if (m_snake[i]->isOnBody(SIRI_Point(x, y)))
					flag = false;
		if (flag)
			m_food.push_back(SIRI_Point(x, y));
	}
}

void gameScene::updateEatFood()
{
	for (int i = 0; i < 2; i++) {
		if (m_snake[i]) {
			int size = m_food.size();
			for (int j = 0; j < size; j++) {
				SIRI_Point point(m_food.front().getX(), m_food.front().getY());
				m_food.pop_front();
				if (point.getX() == m_snake[i]->getHeadPoint().getX() && point.getY() == m_snake[i]->getHeadPoint().getY()) {
					if (!ismute)
						m_win->mMusic->eat->play();
					m_score[i]++;
					m_snake[i]->grow();
					if (m_score[i] % 10 == 0)
						m_snake[i]->speedUp();
				}
				else
					m_food.push_back(point);
			}
		}
	}
}

void gameScene::rend_background()
{
	SIRI_Size winsize = m_win->getSize();
	boxRGBA(m_win->getRenderer(), 0, 0, winsize.getW(), winsize.getH(), 251, 248, 241, 255);
	m_win->Draw(m_win->mImage->map, 20, 20);
	if (m_mod == 1) {
		m_win->Draw(m_win->mImage->preasent_scores, 530, 90);
		m_win->Draw(m_win->mImage->highest_scores, 530, 180);
		m_win->Draw(m_win->mImage->information, 530, 300);
		char str1[20], str2[20];
		sprintf(str1, "%d", m_score[0]);
		sprintf(str2, "%d", m_highestScore);
		m_win->RenderText(str1, Font_kaiti, 570, 115, 40);
		m_win->RenderText(str2, Font_kaiti, 615, 205, 40);
	}
	else {
		m_win->Draw(m_win->mImage->preasent_scoresP1, 530, 90);
		m_win->Draw(m_win->mImage->preasent_scoresP2, 530, 180);
		m_win->Draw(m_win->mImage->information_two, 530, 300);
		char str1[20], str2[20];
		sprintf(str1, "%d", m_score[0]);
		sprintf(str2, "%d", m_score[1]);
		m_win->RenderText(str1, Font_kaiti, 580, 115, 40);
		m_win->RenderText(str2, Font_kaiti, 580, 205, 40);
	}

}

void gameScene::rend_button()
{
	m_muteButton->render();
	m_unmuteButton->render();
	m_backButton->render();
	m_startButton->render();
	m_continueButton->render();
	m_pauseButton->render();
}

void gameScene::rendSnake()
{
	m_snake[0]->render();
	if (m_mod == 2) {
		m_snake[1]->render();
	}

	rendPlayerName();
}

void gameScene::rendDead()
{
	if (m_state == DEAD) {
		m_win->DrawWithAlpha(m_win->mImage->bar, 20, 20,128);
		m_win->Draw(m_win->mImage->gameover, 140, 150);

		if (m_deadFor == NEWSCORE) {
			char str[20];
			sprintf(str, "New Score:%d!", m_score[0]);
			m_win->RenderText(str, Font_kaiti, 130, 350, 40);
		}
		if (m_deadFor == P1WIN) {
			char str[20];
			sprintf(str, "Player1 Win!");
			m_win->RenderText(str, Font_kaiti, 155, 350, 40);
		}
		if (m_deadFor == P2WIN) {
			char str[20];
			sprintf(str, "Player2 Win!");
			m_win->RenderText(str, Font_kaiti, 155, 350, 40);
		}
		if (m_deadFor == NOTHING) {
			if (m_mod == 1) {
				char str[20];
				sprintf(str, "Final Score:%d!", m_score[0]);
				m_win->RenderText(str, Font_kaiti, 130, 350, 40);
			}
			else
			{
				char str[20];
				if (m_score[0] > m_score[1]) {
					sprintf(str, "Player1 Win!");
					m_win->RenderText(str, Font_kaiti, 155, 350, 40);
				}
				else if (m_score[0] < m_score[1]) {
					sprintf(str, "Player2 Win!");
					m_win->RenderText(str, Font_kaiti, 155, 350, 40);
				}
				else {
					sprintf(str, "All Dead!");
					m_win->RenderText(str, Font_kaiti, 200, 350, 40);
				}
			}
		}
	}
}

void gameScene::rendFood()
{
	int size = m_food.size();
	for (int i = 0; i < size; i++) {
		SIRI_Point point(m_food.front().getX(), m_food.front().getY());
		m_win->Draw(m_win->mImage->food, point.getX(), point.getY());
		m_food.pop_front();
		m_food.push_back(point);
	}

}

void gameScene::rendPlayerName()
{
	if (m_mod == 2) {
		for (int i = 0; i < 2; i++) {
			SIRI_Point point = m_snake[i]->getHeadPoint();
			char str[20];
			sprintf(str, "Player%d", i+1);
			m_win->RenderText(str, Font_kaiti, point.getX(), point.getY()-20, 20);
		}
		
	}
}

void gameScene::rendPause()
{
	if (m_state == PAUSE) {
		boxRGBA(m_win->getRenderer(), 20, 20, 520, 520, 255, 255, 255, 100);
		char str[20];
		sprintf(str, "PAUSE");
		m_win->RenderText(str, Font_kaiti, 200, 250, 60);
	}
}

void gameScene::mouseEvent()
{
	int x, y;
	x = events.motion.x;
	y = events.motion.y;

	if (events.button.button == SDL_BUTTON_LEFT) {
		if (m_startButton->isOn())
		{
			if(!ismute)
				m_win->mMusic->click->play();
			m_state = INIT;
		}

		if (m_continueButton->isOn())
		{
			if (!ismute)
				m_win->mMusic->click->play();
			m_state = RUNNING;
		}

		if (m_pauseButton->isOn())
		{
			if (!ismute)
				m_win->mMusic->click->play();
			m_state = PAUSE;
		}

		if (m_muteButton->isOn())
		{
			if (!ismute)
				m_win->mMusic->click->play();
			ismute = false;
		}

		if (m_unmuteButton->isOn())
		{
			ismute = true;
		}

		if (m_backButton->isOn())
		{
			if (!ismute)
				m_win->mMusic->click->play();
			isover = true;
			isescape = false;
		}
	}
}

void gameScene::keyEvent()
{
	switch (events.key.keysym.sym)
	{
	case SDLK_a:
		if (m_state == RUNNING) {
			m_snake[0]->putKey(0);
		}
		break;
	case SDLK_s:
		if (m_state == RUNNING) {
			m_snake[0]->putKey(1);
		}
		break;
	case SDLK_d:
		if (m_state == RUNNING) {
			m_snake[0]->putKey(2);
		}
		break;
	case SDLK_w:
		if (m_state == RUNNING) {
			m_snake[0]->putKey(3);
		}
		break;
	case SDLK_LEFT:
		if (m_state == RUNNING&&m_mod == 2) {
			m_snake[1]->putKey(0);
		}
		break;
	case SDLK_DOWN:
		if (m_state == RUNNING&&m_mod == 2) {
			m_snake[1]->putKey(1);
		}
		break;
	case SDLK_RIGHT:
		if (m_state == RUNNING&&m_mod == 2) {
			m_snake[1]->putKey(2);
		}
		break;
	case SDLK_UP:
		if (m_state == RUNNING&&m_mod == 2) {
			m_snake[1]->putKey(3);
		}
		break;
	case SDLK_v:
		ismute = !ismute;
		break;
	case SDLK_SPACE:
		if (!ismute)
			m_win->mMusic->click->play();
		if (m_state == RUNNING)
			m_state = PAUSE;
		else if (m_state == PAUSE)
			m_state = RUNNING;
		else if (m_state == DEAD)
			m_state = INIT;
		break;
	case SDLK_b:
	case SDLK_ESCAPE:
		if (!ismute)
			m_win->mMusic->click->play();
		isover = true;
		isescape = false;
		break;
	}
}

void gameScene::buttonEvent(SDL_Event& events)
{
	m_muteButton->event(&events);
	m_unmuteButton->event(&events);
	m_backButton->event(&events);
	m_startButton->event(&events);
	m_continueButton->event(&events);
	m_pauseButton->event(&events);
}




bool gameScene::isSnakeDead()
{

	if (m_mod == 1) {
		if (m_snake[0]->isCanMove())
			if (isEatSelf(m_snake[0]) || isOutMap(m_snake[0])) {
				m_state = DEAD;
				if (m_score[0] > m_highestScore) {
					saveScore(ScoreFile, m_score[0]);
					m_deadFor = NEWSCORE;
				}
				else
					m_deadFor = NOTHING;
				m_snake[0]->rollBack();
			}
	}
	else {
		if (m_snake[0]->isCanMove() && m_snake[1]->isCanMove()) {
			if (isEatOthers(m_snake[1], m_snake[0]) && isEatOthers(m_snake[0], m_snake[1])) {
				m_state = DEAD;
				m_deadFor = NOTHING;
				m_snake[0]->rollBack();
				//m_snake[1]->rollBack();
			}
			else if (isEatSelf(m_snake[0])&& isEatSelf(m_snake[1])) {
				m_state = DEAD;
				m_deadFor = NOTHING;
				m_snake[0]->rollBack();
				m_snake[1]->rollBack();
			}
			else if (isOutMap(m_snake[0]) && isOutMap(m_snake[1])) {
				m_state = DEAD;
				m_deadFor = NOTHING;
				m_snake[0]->rollBack();
				m_snake[1]->rollBack();
			}
			else {
				if (isEatSelf(m_snake[0]) || isOutMap(m_snake[0]) || isEatOthers(m_snake[0], m_snake[1])) {
					m_state = DEAD;
					m_deadFor = P2WIN;
					m_snake[0]->rollBack();
				}
				else if (isEatSelf(m_snake[1]) || isOutMap(m_snake[1]) || isEatOthers(m_snake[1], m_snake[0])) {
					m_state = DEAD;
					m_deadFor = P1WIN;
					m_snake[1]->rollBack();
				}
			}
		}
		else if (m_snake[0]->isCanMove())
			if (isEatSelf(m_snake[0]) || isOutMap(m_snake[0]) || isEatOthers(m_snake[0], m_snake[1])) {
				m_state = DEAD;
				m_deadFor = P2WIN;
				m_snake[0]->rollBack();
			}
		else if (m_snake[1]->isCanMove())
			if (isEatSelf(m_snake[1]) || isOutMap(m_snake[1]) || isEatOthers(m_snake[1], m_snake[0])) {
				m_state = DEAD;
				m_deadFor = P1WIN;
				m_snake[1]->rollBack();
			}
		
	}
	
	if (m_state == DEAD) {
		if (!ismute)
			m_win->mMusic->dead->play();
		return true;
	}
	return false;
}

bool gameScene::isOutMap(Snake * snake)
{
	SIRI_Point point = snake->getHeadPoint();
	if (point.getX() < 20)
		return true;
	if (point.getX() > 500)
		return true;
	if (point.getY() < 20)
		return true;
	if (point.getY() > 500)
		return true;
	return false;
}

bool gameScene::isEatSelf(Snake * snake)
{
	return snake->isEatSelf();
}

bool gameScene::isEatOthers(Snake * s1, Snake * s2)
{
	return s2->isOnBody(s1->getHeadPoint());
}

