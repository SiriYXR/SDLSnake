#pragma once

#pragma comment(lib,"SDL2_gfx.lib")

#include "SIRI_Window.h"
#include "SDL2_gfxPrimitives.h"

#include <string>

using namespace std;

namespace siri {

	class SIRI_Button
	{
	private:
		SIRI_Window * m_win;

		SDL_Rect m_rect;
		SDL_Color m_color;
		SDL_Texture* m_img;
		string* m_text;
		string* m_fontFile;

		int m_shadowSize;
		SDL_Color m_shadowColor;

		bool m_isOn;
		bool m_isHiden;
		bool m_isShadowHiden;
	public:
		SIRI_Button(SIRI_Window* win, SDL_Rect rect, SDL_Texture* img = NULL, string* text = NULL, string* fontfile = NULL, SDL_Color* color = NULL, int shadowSize = 2, SDL_Color* shadowColor = NULL);
		SIRI_Button(SIRI_Window* win, SIRI_Rect rect, SDL_Texture* img = NULL, string* text = NULL, string* fontfile = NULL, SDL_Color* color = NULL, int shadowSize = 2, SDL_Color* shadowColor = NULL);
		~SIRI_Button();

		void update();
		void render();
		void event(SDL_Event* events);

		void setIsHiden(bool ishiden);
		void setIsShadowHiden(bool isshadowhiden);

		SIRI_Point& getPoint();
		SDL_Point& getSDLPoint();
		void setPoint(SIRI_Point point);
		void setPoint(SDL_Point point);


		bool isOn();
	};

}