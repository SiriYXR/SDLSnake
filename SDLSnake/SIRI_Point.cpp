#include "SIRI_Point.h"

namespace siri {

	SIRI_Point::SIRI_Point()
	{
		m_x = 0;
		m_y = 0;
	}

	SIRI_Point::SIRI_Point(int x, int y)
	{
		m_x = x;
		m_y = y;
	}


	SIRI_Point::~SIRI_Point()
	{
	}

	int SIRI_Point::getX()
	{
		return m_x;
	}

	int SIRI_Point::getY()
	{
		return m_y;
	}

	void SIRI_Point::setX(int x)
	{
		m_x = x;
	}

	void SIRI_Point::setY(int y)
	{
		m_y = y;
	}

	SDL_Point& SIRI_Point::toSDLPoint()
	{
		SDL_Point point;
		point.x = m_x;
		point.y = m_y;
		return point;
	}

}