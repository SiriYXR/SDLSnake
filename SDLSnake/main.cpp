//=============================
//程序名称：SDLSnake
//版本号：1.0
//制作人：Kazama，SiriYang
//				
//
//创建时间：2018-7-16 19:20:46
//完工时间：2018-7-19 15:50:55
//代码量：2363 行
//制作周期: 4 天
//	
//
//=============================

#include "function.h"

int main(int argc, char **argv)
{
	SIRI_Window *window = new SIRI_Window();
	window->Init(u8"SDL Snake", Win_L, Win_H);//添加u8以支持中文
	openVideo(window);
	mainloop(window);
	endVideo(window);
	window->Quit();
	delete window;

	return 0;
}