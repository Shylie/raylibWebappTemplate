#include "common.h"

static void UpdateDraw();

int main()
{
	Setup();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDraw, 0, 1);
#else
	while (!WindowShouldClose())
	{
		UpdateDraw();
	}
#endif

	Shutdown();

	return 0;
}

static void UpdateDraw()
{
	Update();
	Draw();
}