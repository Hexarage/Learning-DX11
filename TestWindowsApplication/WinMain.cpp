#include "Window.h"

constexpr int width(640), height(480);

int CALLBACK WinMain(
	HINSTANCE hInstance,		// A handle to the current instance of the application
	HINSTANCE /*hPrevInstance*/,// allways null
	LPSTR /*lpCmdLine*/,		// command line, single string, not parsed
	int /*nCmdShow*/			// an instruction on how the window should be shown on program entry
)
{
	Window window(width, height, L"Random Name");
	Window secondWindow(1200, 400, L"Looooooooooong boi");
	
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
	{
		return -1;
	}

	return static_cast<int>(msg.wParam);
}