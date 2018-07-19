#include "menuScene.h"

bool mainloop(SIRI_Window *win)
{
	menuScene scene(win);//实例化主菜单场景对象

	while (true)
	{

		scene.event();//事件判定

		scene.update();//逻辑更新

		if (scene.isOver())//退出场景
			break;

		scene.rend();//渲染界面
	}

	return scene.isEscape();
}