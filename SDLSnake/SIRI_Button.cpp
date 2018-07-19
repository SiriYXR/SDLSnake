#include "SIRI_Button.h"

namespace siri {

	SIRI_Button::SIRI_Button(SIRI_Window * win, SDL_Rect rect, SDL_Texture* img, string * text, string* fontfile, SDL_Color * color, int shadowSize, SDL_Color * shadowColor) : m_win(win), m_img(img)
	{
		m_rect.x = rect.x;
		m_rect.y = rect.y;
		m_rect.w = rect.w;
		m_rect.h = rect.h;

		m_text = text;
		m_fontFile = fontfile;

		if (NULL == color) {
			m_color.r = 255;
			m_color.g = 255;
			m_color.b = 255;
			m_color.a = 255;
		}
		else {
			m_color.r = color->r;
			m_color.g = color->g;
			m_color.b = color->b;
			m_color.a = color->a;
		}

		m_shadowSize = shadowSize;

		if (NULL == shadowColor) {
			m_shadowColor.r = 0;
			m_shadowColor.g = 191;
			m_shadowColor.b = 255;
			m_shadowColor.a = 255;
		}
		else
		{
			m_shadowColor.r = shadowColor->r;
			m_shadowColor.g = shadowColor->g;
			m_shadowColor.b = shadowColor->b;
			m_shadowColor.a = shadowColor->a;
		}

		m_isOn = false;
		m_isHiden = false;
		m_isShadowHiden = false;
	}

	SIRI_Button::SIRI_Button(SIRI_Window * win, SIRI_Rect rect, SDL_Texture * img, string * text, string* fontfile, SDL_Color * color, int shadowSize, SDL_Color * shadowColor) : m_win(win), m_img(img)
	{
		m_rect.x = rect.getX();
		m_rect.y = rect.getY();
		m_rect.w = rect.getW();
		m_rect.h = rect.getH();


		m_text = text;
		m_fontFile = fontfile;

		if (NULL == color) {
			m_color.r = 255;
			m_color.g = 255;
			m_color.b = 255;
			m_color.a = 255;
		}
		else {
			m_color.r = color->r;
			m_color.g = color->g;
			m_color.b = color->b;
			m_color.a = color->a;
		}

		m_shadowSize = shadowSize;

		if (NULL == shadowColor) {
			m_shadowColor.r = 0;
			m_shadowColor.g = 191;
			m_shadowColor.b = 255;
			m_shadowColor.a = 255;
		}
		else
		{
			m_shadowColor.r = shadowColor->r;
			m_shadowColor.g = shadowColor->g;
			m_shadowColor.b = shadowColor->b;
			m_shadowColor.a = shadowColor->a;
		}

		m_isOn = false;
		m_isHiden = false;
		m_isShadowHiden = false;
	}


	SIRI_Button::~SIRI_Button()
	{
		m_win = NULL;
		m_img = NULL;
	}


	void SIRI_Button::update()
	{
	}

	void SIRI_Button::render()
	{
		if (!m_isHiden) {

			if (m_isOn && !m_isShadowHiden)
				boxRGBA(m_win->getRenderer(), m_rect.x - m_shadowSize, m_rect.y - m_shadowSize, m_rect.x + m_rect.w + m_shadowSize, m_rect.y + m_rect.h + m_shadowSize, m_shadowColor.r, m_shadowColor.g, m_shadowColor.b, m_shadowColor.a);

			if (!m_img) {
				int weight = 2;
				boxRGBA(m_win->getRenderer(), m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y + m_rect.h, m_color.r, m_color.g, m_color.b, m_color.a);
				boxRGBA(m_win->getRenderer(), m_rect.x, m_rect.y + m_rect.h - weight, m_rect.x + m_rect.w, m_rect.y + m_rect.h, 119, 136, 153, m_color.a);
				boxRGBA(m_win->getRenderer(), m_rect.x + m_rect.w - weight, m_rect.y, m_rect.x + m_rect.w, m_rect.y + m_rect.h, 119, 136, 153, m_color.a);
			}
			else
			{
				m_win->Draw(m_img, m_rect.x, m_rect.y);
			}

			if (m_fontFile&&m_text)
				m_win->RenderText(*m_text, *m_fontFile, 20, SDL_Color{ 0,0,0 });
		}
	}

	void SIRI_Button::event(SDL_Event* events)
	{
		int x, y;
		x = events->motion.x;
		y = events->motion.y;

		if (events->type == SDL_MOUSEMOTION)
		{
			if ((x > m_rect.x && x < m_rect.x + m_rect.w) && (y > m_rect.y && y < m_rect.y + m_rect.h))
				m_isOn = true;
			else
				m_isOn = false;
		}
	}

	void SIRI_Button::setIsHiden(bool ishiden)
	{
		m_isHiden = ishiden;
	}

	void SIRI_Button::setIsShadowHiden(bool isshadowhiden)
	{
		m_isShadowHiden = isshadowhiden;
	}

	SIRI_Point& SIRI_Button::getPoint()
	{
		return SIRI_Point(m_rect.x, m_rect.y);
	}

	SDL_Point& SIRI_Button::getSDLPoint()
	{
		SDL_Point point;
		point.x = m_rect.x;
		point.y = m_rect.y;
		return point;
	}

	void SIRI_Button::setPoint(SIRI_Point point)
	{
		m_rect.x = point.getX();
		m_rect.y = point.getY();
	}

	void SIRI_Button::setPoint(SDL_Point point)
	{
		m_rect.x = point.x;
		m_rect.y = point.y;
	}

	bool SIRI_Button::isOn()
	{
		if (m_isHiden)
			return false;
		return m_isOn;
	}

}