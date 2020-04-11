#pragma once
#include "WindowsIncludes.h"

#include <d3d11.h>


class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void endFrame();
	void clearBuffer(float red, float green, float blue) noexcept;
private:
	ID3D11Device*			pDevice		=	nullptr; // pointer to d3d11 device that will be filled by D3D11CreateDeviceAndSwapChain
	IDXGISwapChain*			pSwap		=	nullptr; // pointer to the swap chain that will be filled by D3D11CreateDeviceAndSwapChain
	ID3D11DeviceContext*	pContext	=	nullptr; // pointer to the Device Context, will be filled by D3D11CreateDeviceAndSwapChain
	ID3D11RenderTargetView*	pTarget		=	nullptr; // ponter to the render target view (the back buffer) so that it can be accessed during rendering
};

