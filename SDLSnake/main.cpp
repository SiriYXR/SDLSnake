//=============================
//�������ƣ�SDLSnake
//�汾�ţ�1.0
//�����ˣ�Kazama��SiriYang
//				
//
//����ʱ�䣺2018-7-16 19:20:46
//�깤ʱ�䣺2018-7-19 15:50:55
//��������2363 ��
//��������: 4 ��
//	
//
//=============================

#include "function.h"

int main(int argc, char **argv)
{
	SIRI_Window *window = new SIRI_Window();
	window->Init(u8"SDL Snake", Win_L, Win_H);//���u8��֧������
	openVideo(window);
	mainloop(window);
	endVideo(window);
	window->Quit();
	delete window;

	return 0;
}