#include "menuScene.h"

bool mainloop(SIRI_Window *win)
{
	menuScene scene(win);//ʵ�������˵���������

	while (true)
	{

		scene.event();//�¼��ж�

		scene.update();//�߼�����

		if (scene.isOver())//�˳�����
			break;

		scene.rend();//��Ⱦ����
	}

	return scene.isEscape();
}