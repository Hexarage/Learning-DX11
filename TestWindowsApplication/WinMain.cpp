#include "Window.h"
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
		Window window(width, height, L"Random Name");

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			// test app logic
			while (!window.mouse.isEmpty())
			{
				const auto e = window.mouse.read();
				if (e.getType() == Mouse::Event::Type::Move)
				{
					std::ostringstream oss;
					oss << "Mouse Position: (" << e.getPosX() << ", " << e.getPosY() << ")";
					window.setTitle(oss.str());
				}
			}
		}
		if (gResult == -1)
		{
			return -1;
		}

		return static_cast<int>(msg.wParam);
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