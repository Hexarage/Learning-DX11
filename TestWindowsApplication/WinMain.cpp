//#include "Window.h"
#include "LogicHolder.h"

#include <sstream>

constexpr int width(640), height(480);

int CALLBACK WinMain(
	HINSTANCE /*hInstance*/,	// A handle to the current instance of the application
	HINSTANCE /*hPrevInstance*/,// allways null
	LPSTR /*lpCmdLine*/,		// command line, single string, not parsed
	int /*nCmdShow*/			// an instruction on how the window should be shown on program entry
)
{
	try
	{
		return LogicHolder{}.go();
	}
	catch (const ConfuxException & e)
	{
		MessageBoxA(nullptr, e.what(),"Expected Error",MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception & e)
	{
		MessageBoxA(nullptr, e.what(), "Uncaught Error", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available, unexpected error", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}