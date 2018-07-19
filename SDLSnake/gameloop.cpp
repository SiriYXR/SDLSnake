#include "gameScene.h"

bool gameloop(SIRI_Window *win,int mod)
{
	gameScene scene(win,mod);

	while (true)
	{

		scene.event();

		scene.update();

		if (scene.isOver())
			break;

		scene.rend();
	}

	return scene.isEscape();
}