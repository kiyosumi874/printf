#include <Windows.h>
#include "App.h"
// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	App app;
	app.GameLoop();
	return 0;
}