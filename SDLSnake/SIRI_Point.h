#pragma once

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

#include "SDL.h"

namespace siri {

	class SIRI_Point
	{
	public:
		SIRI_Point();
		SIRI_Point(int x, int y);
		~SIRI_Point();

	private:
		int m_x;
		int m_y;

	public:
		int getX();
		int getY();

		void setX(int x);
		void setY(int y);

		SDL_Point& toSDLPoint();
	};

}