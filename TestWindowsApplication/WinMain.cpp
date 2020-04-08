#include <windows.h>
constexpr int xpos(400), ypos(400), width(640), height(480);
int CALLBACK WinMain(
	HINSTANCE hInstance,		// A handle to the current instance of the application
	HINSTANCE hPrevInstance,	// allways null
	LPSTR lpCmdLine,			// command line, single string, not parsed
	int nCmdShow				// an instruction on how the window should be shown on program entry
)
{
	const LPCWSTR pClassName = L"Hardware3DStuff";
	// register window class
	WNDCLASSEX windowsClass = { 0 };
	windowsClass.cbSize			=	sizeof(windowsClass);	// size of the structure
	windowsClass.style			=	CS_OWNDC;				// style of the class, CS_OWNDC -> Allocates a unique device context for each window in the class; DC = Device Context
	windowsClass.lpfnWndProc	=	DefWindowProc;			// long pointer to function Window Proc, pointer to a handler function
	windowsClass.cbClsExtra		=	0;						// Allows to allocate extra bytes of memory following the window-class structure
	windowsClass.cbWndExtra		=	0;						// Create extra bytes within every instance
	windowsClass.hInstance		=	hInstance;				// The thing we get from WinMain
	windowsClass.hIcon			=	nullptr;				// Custom Icon
	windowsClass.hCursor		=	nullptr;				// Custom cursor, usually set to null so we get the default
	windowsClass.hbrBackground	=	nullptr;				// GDI thing, set to null so that we draw the background ourselves
	windowsClass.lpszMenuName	=	nullptr;				// pointer to a null terminated character string that specifies the nae  of the class menu as the name appears in the resource file. NULL
	windowsClass.lpszClassName	=	pClassName;				// Name that will be used when we create windows of this class type
	windowsClass.hIconSm		=	nullptr;				// Custom Icon stuff
	RegisterClassEx(&windowsClass);

	// create window instance

	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		L"De Windo",										// name of the window
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,			// go to docs.microsoft.com/en-us/windows/desktop/winmsg/window-styles for more flags and what they do specifically
		xpos,
		ypos,
		width,
		height,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// show window

	ShowWindow(hWnd, SW_SHOW);

	while (true);
	return 0;
}