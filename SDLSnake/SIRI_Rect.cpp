#include "SIRI_Rect.h"

#pragma comment(lib,"SDL2_image.lib")
#include "SDL_image.h"

namespace siri {

	SIRI_Rect::SIRI_Rect()
	{
		m_x = 0;
		m_y = 0;
		m_w = 0;
		m_h = 0;
	}

	SIRI_Rect::SIRI_Rect(int x, int y, int w, int h)
	{
		m_x = x;
		m_y = y;
		m_w = w;
		m_h = h;
	}

	SIRI_Rect::SIRI_Rect(SDL_Rect rect)
	{
		m_x = rect.x;
		m_y = rect.y;
		m_w = rect.w;
		m_h = rect.h;
	}

	SIRI_Rect::SIRI_Rect(int x, int y, SDL_Texture * img)
	{
		if (img) {
			m_x = x;
			m_y = y;
			SDL_QueryTexture(img, NULL, NULL, &m_w, &m_h);
		}
		else {
			m_x = 0;
			m_y = 0;
			m_w = 0;
			m_h = 0;
		}
	}


	SIRI_Rect::~SIRI_Rect()
	{
	}

	SIRI_Point& SIRI_Rect::getPoint()
	{
		return SIRI_Point(m_x,m_y);
	}

	SIRI_Size& SIRI_Rect::getSize()
	{
		return SIRI_Size(m_w,m_y);
	}

	SDL_Point& SIRI_Rect::getSDLPoint()
	{
		return SIRI_Point(m_x, m_y).toSDLPoint();
	}

	int SIRI_Rect::getX()
	{
		return m_x;
	}
	int SIRI_Rect::getY()
	{
		return m_y;
	}
	int SIRI_Rect::getW()
	{
		return m_w;
	}
	int SIRI_Rect::getH()
	{
		return m_h;
	}
	void SIRI_Rect::setX(int x)
	{
		m_x = x;
	}
	void SIRI_Rect::setY(int y)
	{
		m_y = y;
	}
	void SIRI_Rect::setW(int w)
	{
		m_w = w;
	}
	void SIRI_Rect::setH(int h)
	{
		m_h = h;
	}
	SDL_Rect& SIRI_Rect::toSDLRect()
	{
		SDL_Rect rect;
		rect.x = m_x;
		rect.y = m_y;
		rect.w = m_w;
		rect.h = m_h;
		return rect;
	}
}


