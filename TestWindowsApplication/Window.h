#pragma once
#include "WindowsIncludes.h"
#include "ConfuxException.h"
#include "Keyboard.h"
#include "Mouse.h"

// Class for the creation and destruction of a window as well as message handling, maybe separate the functionality
class Window
{
public:
	class Exception : public ConfuxException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* getType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT getErrorCode() const noexcept;
		std::string getErrorString() const noexcept;
	private:
		HRESULT hr;
	};
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
	Window(int width, int height, const LPCWSTR name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void setTitle(const std::string newTitle);
private:
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keyboard;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
};

//error exception helper macro, basically helps me not type out __LINE__ and __FILE__ Macros every time I make an exception
#define CNFXWND_EXCEPT( hr ) Window::Exception(__LINE__, __FILE__, hr)
#define CNFXWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())