#include "common.h"

AppState appState;

void Setup()
{
	InitWindow(1920, 1080, "app");
	SetTargetFPS(60);

	// setup appState here
}

void Update()
{
	// update appState here
}

void Draw()
{
	BeginDrawing();

	// do any drawing here
	ClearBackground(WHITE);

	DrawLineEx({ 1920 / 2, 1080 / 2 }, GetMousePosition(), 2.5f, RED);

	EndDrawing();
}

void Shutdown()
{
	// do any cleanup of appState here

	CloseWindow();
}