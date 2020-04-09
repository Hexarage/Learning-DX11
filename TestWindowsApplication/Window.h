#pragma once
#include "WindowsIncludes.h"

// Class for the creation and destruction of a window as well as message handling, maybe separate the functionality
class Window
{
private:
	// Singleton that manages the registration/cleanup of window class
	class WindowOverhead
	{
	public:
		static const LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowOverhead() noexcept;
		~WindowOverhead();
		WindowOverhead(const WindowOverhead&) = delete;
		WindowOverhead& operator=(const WindowOverhead&) = delete;
		static constexpr LPCWSTR wndClassName = L"Hex tries Direct3D Engine Window";
		static WindowOverhead windowOverhead;
		HINSTANCE hInstance;
	};
public:
	Window(int width, int height, const LPCWSTR name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
};