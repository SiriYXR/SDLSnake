#include "function.h"

#include <fstream>
#include <time.h>

void openVideo(SIRI_Window *win)
{
	
	for (int x = -780; x <=0; x += 20){
		win->Clear();

		win->Draw(win->mImage->intogame, x, 0);

		win->Present();
		SDL_Delay(15);
	}
	for (int x = 0; x >= -80; x -= 10) {
		win->Clear();

		win->Draw(win->mImage->intogame, x, 0);

		win->Present();
		SDL_Delay(15);
	}for (int x = -80; x <= 0; x += 5) {
		win->Clear();

		win->Draw(win->mImage->intogame, x, 0);

		win->Present();
		SDL_Delay(15);
	}
	SDL_Delay(200);
}

void endVideo(SIRI_Window *win)
{
	win->Clear();

	win->Draw(win->mImage->outgame, 0, 0);

	win->Present();

	SDL_Delay(2000);
}

void saveScore(string file,int score)
{
	fstream ofs;//实例化文件输出流
	ofs.open(file,ios::out);
	if (!ofs)
		throw std::runtime_error(file + " open failed!");//若文件打开失败则抛出异常
	ofs << score;//向文件输出分数
	ofs.close();//关闭文件流
}

int readScore(string file)
{
	fstream ifs(file, ios::in);

	if(!ifs)
		throw std::runtime_error(file + " open failed!");
	int score=0;
	ifs >> score;
	ifs.close();

	return score;
}

