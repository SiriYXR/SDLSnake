#include "aboutusScene.h"

bool aboutusloop(SIRI_Window *win)
{
	aboutusScene scene(win);

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