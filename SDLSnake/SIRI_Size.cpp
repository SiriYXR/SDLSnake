#include "SIRI_Size.h"

namespace siri {

	


	SIRI_Size::SIRI_Size()
	{
		m_w = 0;
		m_h = 0;
	}

	SIRI_Size::SIRI_Size(int w, int h)
	{
		m_w = w;
		m_h = h;
	}

	SIRI_Size::~SIRI_Size()
	{
	}

	int SIRI_Size::getW()
	{
		return m_w;
	}

	int SIRI_Size::getH()
	{
		return m_h;
	}

	void SIRI_Size::setW(int w)
	{
		m_w = w;
	}

	void SIRI_Size::setH(int h)
	{
		m_h = h;
	}

}