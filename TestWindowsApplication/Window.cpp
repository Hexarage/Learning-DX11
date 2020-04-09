#include "Window.h"
#include <sstream>

Window::WindowOverhead Window::WindowOverhead::windowOverhead;

Window::WindowOverhead::WindowOverhead() noexcept
	:
	hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wndCl	=	{ 0 };
	wndCl.cbSize		=	sizeof(wndCl);
	wndCl.style			=	CS_OWNDC;
	wndCl.lpfnWndProc	=	HandleMsgSetup;
	wndCl.cbClsExtra	=	0;
	wndCl.cbWndExtra	=	0;
	wndCl.hInstance		=	GetInstance();
	wndCl.hIcon			=	nullptr;
	wndCl.hCursor		=	nullptr;
	wndCl.hbrBackground	=	nullptr;
	wndCl.lpszMenuName	=	nullptr;
	wndCl.lpszClassName	=	GetName();
	wndCl.hIconSm		=	nullptr;
	RegisterClassEx(&wndCl);
}

Window::WindowOverhead::~WindowOverhead()
{
	UnregisterClass(wndClassName, GetInstance());
}

const LPCWSTR Window::WindowOverhead::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowOverhead::GetInstance() noexcept
{
	return windowOverhead.hInstance;
}

Window::Window(int width, int height, const LPCWSTR name) noexcept
{
	//Calculate window size based on desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	// Create window and get hWnd
	hWnd = CreateWindow(WindowOverhead::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowOverhead::GetInstance(), this);

	// Show Window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // This is only to set up our Window pointer (last parameter given to CreateWindow in Window::Window(...) where hWnd is set)
{
	//use create parameter passed in from CreateWindow() to store window class pointer
	if (msg == WM_NCCREATE)
	{
		// Extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// Set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Since set up is finished, set message proc to normal (non-setup) handler
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// Forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	// If we get a message before the WM_NCCREATE message, handle it with the default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // basically adapts from win32 call convention to cpp call convention so we can access our class properly
{
	// Retrieve pointer to Window class
	Window* const ptr2Wnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return ptr2Wnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWndPass, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0; // Destroy Window gets called in the destructor of Window, we don't want it called twice by  DefWindowProc
	}

	return DefWindowProc(hWndPass, msg, wParam, lParam);
}

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	ConfuxException(line, file),
	hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;

	oss << getType() << "\n"
		<< "[ERROR CODE]: " << getErrorCode() << "\n"
		<< "[DESCRIPTION]: " << getErrorString() << "\n"
		<< getOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::getType() const noexcept
{
	return "Confux Window Exception"; // TODO: Figure out better name/type
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuffer = nullptr;
	DWORD nMsgLength = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // Allocates memory for us
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //MAKELANGID is deprecated TODO: Change to a non deprecated function/alternative
		reinterpret_cast<LPSTR>(&pMsgBuffer), 0, nullptr);
	if (nMsgLength == 0)
	{
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuffer;
	LocalFree(pMsgBuffer);
	return errorString;
}

HRESULT Window::Exception::getErrorCode()const noexcept
{
	return hr;
}

std::string Window::Exception::getErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}