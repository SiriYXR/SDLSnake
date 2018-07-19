#pragma once

#include "SIRI_Graphics.h"

namespace siri {

	class SIRI_Image
	{
	public:
		SIRI_Image(SDL_Renderer *Ren);
		~SIRI_Image();

		//º”‘ÿÕº∆¨
		SDL_Texture * LoadImage(const std::string & file);
		void delimage(SDL_Texture* image);

	private:
		SDL_Renderer *Renderer = nullptr;

	public:
		SDL_Surface *icon = nullptr;

		//button
		SDL_Texture *back = nullptr;
		SDL_Texture *isVoice = nullptr;
		SDL_Texture *noVoice = nullptr;
		SDL_Texture *continu = nullptr;
		SDL_Texture *pause = nullptr;
		SDL_Texture *start = nullptr;
		SDL_Texture *switch_oneplayer = nullptr;
		SDL_Texture *switch_twoplayer = nullptr;
		SDL_Texture *switch_startgame = nullptr;
		SDL_Texture *aboutus_button = nullptr;

		//interface
		SDL_Texture *bar = nullptr;
		SDL_Texture *director = nullptr;
		SDL_Texture *food = nullptr;
		SDL_Texture *gameover = nullptr;
		SDL_Texture *highest_scores = nullptr;
		SDL_Texture *information = nullptr;
		SDL_Texture *information_two = nullptr;
		SDL_Texture *intogame = nullptr;
		SDL_Texture *map = nullptr;
		SDL_Texture *outgame = nullptr;
		SDL_Texture *preasent_scores = nullptr;
		SDL_Texture *preasent_scoresP1 = nullptr;
		SDL_Texture *preasent_scoresP2 = nullptr;
		SDL_Texture *aboutus_interface = nullptr;

		//snake
		SDL_Texture *body = nullptr;
		SDL_Texture *head_A = nullptr;
		SDL_Texture *head_D = nullptr;
		SDL_Texture *head_S = nullptr;
		SDL_Texture *head_W = nullptr;
		SDL_Texture *tail_A = nullptr;
		SDL_Texture *tail_D = nullptr;
		SDL_Texture *tail_S = nullptr;
		SDL_Texture *tail_W = nullptr;
	};

}