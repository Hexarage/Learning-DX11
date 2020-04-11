#include "LogicHolder.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

LogicHolder::LogicHolder()
	:
	window(800, 600, L"De Windo")
{}

int LogicHolder::go()
{
	MSG msg;
	BOOL gResult;
	while (true)
	{
		//process all messages pending, but to not block
		if (const auto ecode = Window::processMessages()) // optional evaluates to true if it has a value
		{
			return *ecode;
		}
		doFrame();
	}

	//check if GetMessage call itself messed up
	if (gResult == -1)
	{
		throw CNFXWND_LAST_EXCEPT();
	}

	//wParam here is the value passed to PostQuitMessage
	return static_cast<int>(msg.wParam);
}

void LogicHolder::doFrame()
{
	const float c = sin(timer.peek()) / 2.0f + 0.5f;
	window.graphics().clearBuffer(c, c, 1.0f-std::max(c/4.0f,0.25f));
	window.graphics().endFrame();
}