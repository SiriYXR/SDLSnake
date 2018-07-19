#include "choiceScene.h"

bool choiceloop(SIRI_Window *win)
{
	choiceScene scene(win);

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