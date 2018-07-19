#include "SIRI_Image.h"

#pragma comment(lib,"SDL2_image.lib")
#include "SDL_image.h"

namespace siri {

	SIRI_Image::SIRI_Image(SDL_Renderer *Ren) :Renderer(Ren)
	{

		icon = IMG_Load("data/image/icon/icon.jpg");

		back = LoadImage("data/image/button/back.png");
		isVoice = LoadImage("data/image/button/isVoice.png");
		noVoice = LoadImage("data/image/button/noVoice.png");
		continu = LoadImage("data/image/button/continu.png");
		pause = LoadImage("data/image/button/pause.png");
		start = LoadImage("data/image/button/start.png");
		switch_oneplayer = LoadImage("data/image/button/switch_oneplayer.png");
		switch_twoplayer = LoadImage("data/image/button/switch_twoplayer.png");
		switch_startgame = LoadImage("data/image/button/switch_startgame.png");
		aboutus_button = LoadImage("data/image/button/aboutus.png");

		bar = LoadImage("data/image/interface/bar.jpg");
		director = LoadImage("data/image/interface/director.png");
		food = LoadImage("data/image/interface/food.jpg");
		gameover = LoadImage("data/image/interface/gameover.png");
		highest_scores = LoadImage("data/image/interface/highest_scores.jpg");
		information = LoadImage("data/image/interface/information.jpg");
		information_two = LoadImage("data/image/interface/information_two.png");
		intogame = LoadImage("data/image/interface/intogame.png");
		map = LoadImage("data/image/interface/map.jpg");
		outgame = LoadImage("data/image/interface/outgame2.png");
		preasent_scores = LoadImage("data/image/interface/preasent_scores.jpg");
		preasent_scoresP1 = LoadImage("data/image/interface/preasent_scoresP1.jpg");
		preasent_scoresP2 = LoadImage("data/image/interface/preasent_scoresP2.jpg");
		aboutus_interface = LoadImage("data/image/interface/aboutus.jpg");

		body = LoadImage("data/image/snake/body.jpg");
		head_A = LoadImage("data/image/snake/head_A.jpg");
		head_D = LoadImage("data/image/snake/head_D.jpg");
		head_S = LoadImage("data/image/snake/head_S.jpg");
		head_W = LoadImage("data/image/snake/head_W.jpg");
		tail_A = LoadImage("data/image/snake/tail_A.jpg");
		tail_D = LoadImage("data/image/snake/tail_D.jpg");
		tail_S = LoadImage("data/image/snake/tail_S.jpg");
		tail_W = LoadImage("data/image/snake/tail_W.jpg");
	}


	SIRI_Image::~SIRI_Image()
	{
		SDL_FreeSurface(icon);

		delimage(back);
		delimage(isVoice);
		delimage(noVoice);
		delimage(continu);
		delimage(pause);
		delimage(start);
		delimage(switch_oneplayer);
		delimage(switch_twoplayer);
		delimage(switch_startgame);
		delimage(aboutus_button);

		delimage(bar);
		delimage(director);
		delimage(food);
		delimage(gameover);
		delimage(highest_scores);
		delimage(information);
		delimage(information_two);
		delimage(intogame);
		delimage(map);
		delimage(outgame);
		delimage(preasent_scores);
		delimage(preasent_scoresP1);
		delimage(preasent_scoresP2);
		delimage(aboutus_interface);

		delimage(body);
		delimage(head_A);
		delimage(head_D);
		delimage(head_S);
		delimage(head_W);
		delimage(tail_A);
		delimage(tail_D);
		delimage(tail_S);
		delimage(tail_W);
	}

	SDL_Texture * SIRI_Image::LoadImage(const std::string & file)
	{
		return siri::LoadTexture(Renderer, file.c_str());
	}

	void SIRI_Image::delimage(SDL_Texture * image)
	{
		siri::DelTexture(image);
	}

}