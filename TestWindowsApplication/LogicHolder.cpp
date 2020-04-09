#include "LogicHolder.h"
#include <sstream>
#include <iomanip>

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
	const float t = timer.peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(2) << t << "seconds";
	window.setTitle(oss.str());
}