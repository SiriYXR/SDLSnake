#include "Snake.h"



Snake::Snake(SIRI_Window * win, SIRI_Point point, int direction)
{
	m_win = win;
	m_headPoint = point;
	m_headDir = direction;
	m_speed = 1.0;
	m_count = 0.0;

	m_nodeHead = new Node;
	m_nodeTail = new Node;
	m_nodeHead->next = m_nodeTail;
	m_nodeHead->prev = NULL;
	m_nodeTail->next = NULL;
	m_nodeTail->prev = m_nodeHead;

	Node* p;
	for (m_length = 0; m_length < 3; m_length++)
	{
		p = new Node;
		p->x = m_headPoint.getX() - m_length*Dir[m_headDir].x * 20;
		p->y = m_headPoint.getY() - m_length*Dir[m_headDir].y * 20;
		p->direction = m_headDir;
		p->next = NULL;
		if (m_nodeHead->next == m_nodeTail)
		{
			m_nodeHead->next = p;
			p->prev = m_nodeHead;
			p->next = m_nodeTail;
			m_nodeTail->prev = p;
		}
		else
		{
			p->prev = m_nodeTail->prev;
			p->next = m_nodeTail;
			m_nodeTail->prev->next = p;
			m_nodeTail->prev = p;
		}
	}

	m_isCanAccelerate = true;
	m_accelerate = 0;
}


Snake::~Snake()
{
	clear();
	delete m_nodeHead;
	delete m_nodeTail;
	m_nodeHead = NULL;
	m_nodeTail = NULL;
}

void Snake::update()
{
	updateCount();
	updateHeadDir();
	updateMove();
	updateHeadPoint();
	if (m_accelerate)
		m_accelerate--;
	
}

void Snake::render()
{
	Node* p;
	p = m_nodeHead->next;
	while (p != m_nodeTail) {
		if (p == m_nodeHead->next) {
			switch (p->direction)
			{
			case 0:
				m_win->Draw(m_win->mImage->head_A, p->x, p->y);
				break;
			case 1:
				m_win->Draw(m_win->mImage->head_S, p->x, p->y);
				break;
			case 2:
				m_win->Draw(m_win->mImage->head_D, p->x, p->y);
				break;
			case 3:
				m_win->Draw(m_win->mImage->head_W, p->x, p->y);
				break;
			default:
				break;
			}
		}
		else if (p == m_nodeTail->prev) {
			switch (p->direction)
			{
			case 0:
				m_win->Draw(m_win->mImage->tail_A, p->x, p->y);
				break;
			case 1:
				m_win->Draw(m_win->mImage->tail_S, p->x, p->y);
				break;
			case 2:
				m_win->Draw(m_win->mImage->tail_D, p->x, p->y);
				break;
			case 3:
				m_win->Draw(m_win->mImage->tail_W, p->x, p->y);
				break;
			default:
				break;
			}
		}
		else
		{
			m_win->Draw(m_win->mImage->body, p->x, p->y);
		}

		p = p->next;
	}
}

void Snake::putKey(int key)
{
	if (key == m_headDir) {
		if(m_isCanAccelerate)
			m_accelerate = 2;
		return;
	}
	if (m_key.size() < 3)
		m_key.push_back(key);
}



SIRI_Point & Snake::getHeadPoint()
{
	return m_headPoint;
}

SIRI_Point & Snake::getNextHeadPoint()
{
	int dir = m_headDir;

	if (!m_key.empty()) {
		int k = m_key.front();
		switch (k)
		{
		case 0:
		case 2:
			if (k == 1 || k == 3)
				dir = k;
			break;
		case 1:
		case 3:
			if (k == 0 || k == 2)
				dir = k;
			break;
		default:
			break;
		}
	}

	int x = m_headPoint.getX();
	int y = m_headPoint.getY();
	x += Dir[dir].x * 20;
	y += Dir[dir].y * 20;

	return SIRI_Point(x, y);
}

void Snake::grow()
{
	pushBack();
}

bool Snake::isEatSelf()
{
	int x = getHeadPoint().getX();
	int y = getHeadPoint().getY();
	Node* p;
	p = m_nodeHead->next->next;
	while (p != m_nodeTail) {
		if (p->x == x&&p->y == y)
			return true;
		p = p->next;
	}

	return false;
}

bool Snake::isOnBody(SIRI_Point point)
{
	int x = point.getX();
	int y = point.getY();
	Node* p;
	p = m_nodeHead->next;
	while (p != m_nodeTail) {
		if (p->x == x&&p->y == y)
			return true;
		p = p->next;
	}

	return false;
}

void Snake::pushBack()
{
	Node* p = new Node;
	p->direction = m_nodeTail->prev->direction;

	p->x = m_nodeTail->prev->x ;
	p->y = m_nodeTail->prev->y ;

	p->next = m_nodeTail;
	p->prev = m_nodeTail->prev;
	p->prev->next = p;
	m_nodeTail->prev = p;

	m_length++;

}

bool Snake::popFront()
{
	if (!isEmpty())
	{
		Node* p;
		p = m_nodeHead->next;
		m_nodeHead->next = p->next;
		p->next->prev = m_nodeHead;
		delete p;
		m_length--;
		return true;
	}
	else
		return false;
}

int Snake::getLength()
{
	return m_length;
}

bool Snake::isEmpty()
{
	return m_length == 0 ? true : false;
}

void Snake::clear()
{
	while (!isEmpty()) {
		popFront();
	}
}

void Snake::updateCount()
{

	if (m_count > 20)
		m_count = 0;
	if(m_accelerate)
		m_count += m_speed+5;
	m_count += m_speed;
}

void Snake::updateMove()
{
	if (isCanMove()) {
		Node* p;
		p = m_nodeTail->prev;
		while (p != m_nodeHead->next) {
			p->x = p->prev->x;
			p->y = p->prev->y;
			p->direction = p->prev->direction;
			p = p->prev;
		}
		p->direction = m_headDir;
		p->x += Dir[p->direction].x * 20;
		p->y += Dir[p->direction].y * 20;
	}
}

void Snake::updateHeadDir()
{
	if (isCanMove()) {
		if (!m_key.empty()) {
			int k = m_key.front();
			m_key.pop_front();
			switch (m_headDir)
			{
			case 0:
			case 2:
				if (k == 1 || k == 3)
					m_headDir = k;
				break;
			case 1:
			case 3:
				if (k == 0 || k == 2)
					m_headDir = k;
				break;
			default:
				break;
			}
		}
	}
}

void Snake::updateHeadPoint()
{
	m_headPoint.setX(m_nodeHead->next->x);
	m_headPoint.setY(m_nodeHead->next->y);
}

bool Snake::isCanMove()
{
	return m_count > 20 ? true : false;
}

void Snake::rollBack()
{
	Node* p;
	p = m_nodeHead->next;
	p->x = p->next->x;
	p->y = p->next->y;
	p = p->next;
	while (p != m_nodeTail->prev) {
		p->x = p->next->x;
		p->y = p->next->y;
		p->direction = p->next->direction;
		p = p->next;
	}
	p->direction = m_nodeTail->prev->direction;
	p->x -= Dir[p->direction].x * 20;
	p->y -= Dir[p->direction].y * 20;
}

void Snake::speedUp()
{
	if (m_speed < SpeedMax)
		m_speed += 0.2;
}

void Snake::setAccelerate(bool iscan)
{
	m_isCanAccelerate = iscan;
}
