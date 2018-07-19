#pragma once
#include "SIRI_Point.h"
#include "SIRI_Size.h"

namespace siri {

	class SIRI_Rect
	{
	public:
		SIRI_Rect();
		SIRI_Rect(int x, int y, int w, int h);
		SIRI_Rect(SDL_Rect rect);
		SIRI_Rect(int x,int y,SDL_Texture* img);
		~SIRI_Rect();
	private:
		int m_x;
		int m_y;
		int m_w;
		int m_h;
	public:

		SIRI_Point& getPoint();
		SIRI_Size& getSize();
		SDL_Point& getSDLPoint();

		int getX();
		int getY();
		int getW();
		int getH();

		void setX(int x);
		void setY(int y);
		void setW(int w);
		void setH(int h);

		SDL_Rect& toSDLRect();
	};

}

