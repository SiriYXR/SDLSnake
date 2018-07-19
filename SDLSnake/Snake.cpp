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

	m_isCanAccelerate = true;//默认可以加速
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
	if (m_accelerate)//更新加速计数器
		m_accelerate--;
	
}

void Snake::render()
{
	Node* p;
	p = m_nodeHead->next;
	while (p != m_nodeTail) {
		if (p == m_nodeHead->next) {//根据方向打印蛇头
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
		else if (p == m_nodeTail->prev) {//根据方向打印蛇尾
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
		else//打印身体
		{
			m_win->Draw(m_win->mImage->body, p->x, p->y);
		}

		p = p->next;
	}
}

void Snake::putKey(int key)
{
	if (key == m_headDir) {//如果操作指令和蛇头方向一样
		if(m_isCanAccelerate)//且可以加速的话
			m_accelerate = 2;//更新加速计数器
		return;
	}
	if (m_key.size() < 3)//如果操作指令链表不超过3，将操作指令加入操作指令链表
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
	//获取蛇头位置
	int x = getHeadPoint().getX();
	int y = getHeadPoint().getY();
	//跳过蛇头遍历之后的所有蛇身
	Node* p;
	p = m_nodeHead->next->next;
	while (p != m_nodeTail) {
		if (p->x == x&&p->y == y)//如果和蛇身任意一个结点重合就判定为真
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

	if (m_count > 20)//如果计数器超过20则清零
		m_count = 0;
	if(m_accelerate)//如果加速状态不为0，则计数器加速计时
		m_count += m_speed+5;
	m_count += m_speed;
}

//从尾部向头遍历蛇身结点，每个结点复制前一个结点的状态，直到头结点根据自身方向计算新的位置，以实现蛇向前移动一步的效果。
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
		if (!m_key.empty()) {//如果指令链表不为空，取第一个操作指令，否则保持原有方向
			int k = m_key.front();
			m_key.pop_front();
			switch (m_headDir)//如果指令方向和现有方向垂直则更新现有方向
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
	return m_count > 20 ? true : false;//如果计数器超过20则可以移动
}

//从头部向后遍历，每个结点复制后一个结点的状态，直到尾部结点根据方向更新位置，以实现蛇向后倒退一步的效果。特别地，蛇头方向保留不做改变
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

void Snake::setAccelerate(bool iscan)//设置加速状态
{
	m_isCanAccelerate = iscan;
}
