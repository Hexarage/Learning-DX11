#include "Graphics.h"

#pragma comment(lib, "d3d11.lib") // settings get set for us

Graphics::Graphics(HWND hWnd)
{
	// Create the descriptor structure
	DXGI_SWAP_CHAIN_DESC descStruct = {};
	descStruct.BufferDesc.Width = 0;												// Look at the window and figure out the width
	descStruct.BufferDesc.Height = 0;												// =//= height
	descStruct.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;						// The layout of the pixels (8 bits for rgba and the actual layout is blue green red alpha)
	descStruct.BufferDesc.RefreshRate.Numerator = 0;								// refreshrate is already there
	descStruct.BufferDesc.RefreshRate.Denominator = 0;								// =//=
	descStruct.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// Scaling really shouldn't be there
	descStruct.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// If it's interlaced, there would be a scanline order
	descStruct.SampleDesc.Count = 1;												// antialiasing stuff, basically make it so it doesn't happen
	descStruct.SampleDesc.Quality = 0;												//
	descStruct.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;						// We want this buffer to be used as render target
	descStruct.BufferCount = 1;														// We want two, so we say there is 1 back buffer, dumb way to do it..
	descStruct.OutputWindow = hWnd;													// The handle to the window which will be used as output
	descStruct.Windowed = TRUE;														// windowed yes, yes yes
	descStruct.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;								// The default, also possibly best performance
	descStruct.Flags = 0;															// describes options for swap-chain behaviour, TODO: Play around with this

	// Create device and front and back buffers as well as swap chain and rendering context
	D3D11CreateDeviceAndSwapChain(		// TODO: add error checking
		nullptr,						// pointer to IDXGIAdapter, null chooses the default
		D3D_DRIVER_TYPE_HARDWARE,		// Noting that we want a hardware device
		nullptr,						// A handle to a binary for when we want to load a software driver
		0,								// Flags
		nullptr,						// Feature level
		0,								// more feature level stuff
		D3D11_SDK_VERSION,				// What SDK version we're targeting
		&descStruct,					// Pointer to a descriptor structure
		&pSwap,							// pointer to pointer to swap chain
		&pDevice,						// pointer to pointer to device
		nullptr,						// output pointer to feature level
		&pContext						// ptp to Context
	);

	// Gain access to the thexture subresource in the swap cahin (back buffer)
	ID3D11Resource* pBackBuffer = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	if (pBackBuffer)
	{
		pDevice->CreateRenderTargetView(
			pBackBuffer,
			nullptr,
			&pTarget
		);
		pBackBuffer->Release();// We don't need this handle any more
	}
}

Graphics::~Graphics()	// TODO: Restructure so that children are released first, it looks tidyer
{
	if (pDevice)
	{
		pDevice->Release();
	}
	if (pSwap)
	{
		pSwap->Release();
	}
	if (pContext)
	{
		pContext->Release();
	}
	if (pTarget)
	{
		pTarget->Release();
	}
}

void Graphics::endFrame()
{
	pSwap->Present(1u/*SyncInterval 1u targets 60fps, 2u targets 30fps*/, 0u);
}

void Graphics::clearBuffer(float red, float green, float blue) noexcept
{
	const float colour[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget, colour);
}
