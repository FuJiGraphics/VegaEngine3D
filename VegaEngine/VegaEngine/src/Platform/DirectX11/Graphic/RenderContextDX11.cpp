#include "pch.h"
#include "Core/Graphic/IRenderContext.h"
#include "RenderContextDX11.h"
#include "Core/IWindow.h"

namespace vega {

	RenderContextDX11::RenderContextDX11()
		: m_pDevice(nullptr)
		, m_pDeviceContext(nullptr)
		, m_pSwapChain(nullptr)
		, m_pRenderTargetView(nullptr)
	{
		// Empty
	}

	RenderContextDX11::~RenderContextDX11()
	{
		this->Release();
	}

	void RenderContextDX11::Init(const IWindow& window)
	{
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo((SDL_Window*)window.GetNativeWindow(), &wmInfo);
		HWND hwnd = (HWND)wmInfo.info.win.window;

		CreateDeviceAndSwapChain(hwnd);
		CreateRenderTargetView();
	}

	void RenderContextDX11::Release()
	{
		CleanupRenderTargetView();
	}

	void RenderContextDX11::Init_ImGui()
	{
		FZLOG_ASSERT(ImGui_ImplDX11_Init(m_pDevice, m_pDeviceContext), "Failed to initialized a ImGui_ImplDX11_Init");
	}

	void RenderContextDX11::Release_ImGui()
	{
		ImGui_ImplDX11_Shutdown();
	}

	void RenderContextDX11::Render()
	{
		ImGui::Render();
		const float clear_color_with_alpha[4] = { 0.10f, 0.10f, 0.10f, 1.0f }; 
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
		// Update and Render additional Platform Windows
		// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	void RenderContextDX11::Present()
	{
		m_pSwapChain->Present(1, 0); // Present with vsync
		//g_pSwapChain->Present(0, 0); // Present without vsync
	}

	void RenderContextDX11::CreateRenderTargetView()
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		if (pBackBuffer != nullptr)
		{
			m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
			pBackBuffer->Release();
		}
		else
		{
			FZLOG_ASSERT(pBackBuffer != nullptr, "Failed to generate back buffer!")
		}
	}

	void RenderContextDX11::CreateDeviceAndSwapChain(HWND hwnd)
	{
		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { 
			D3D_FEATURE_LEVEL_11_0, 
			D3D_FEATURE_LEVEL_10_0, 
		};
		
		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createDeviceFlags,
			featureLevelArray,
			2,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&m_pDevice,
			&featureLevel,
			&m_pDeviceContext
		);	// != S_OK is failed

		FZLOG_ASSERT(result == S_OK, "Faileid to create d3d11 device and Swapchain");
	}

	void RenderContextDX11::CleanupRenderTargetView()
	{
		if (m_pRenderTargetView) 
		{ 
			m_pRenderTargetView->Release();
			m_pRenderTargetView = nullptr;
		}
	}

	void RenderContextDX11::CleanupDeviceAndSwapChain()
	{
		CleanupRenderTargetView();
		if (m_pSwapChain) 
		{ 
			m_pSwapChain->Release(); 
			m_pSwapChain = nullptr; 
		}
		if (m_pDeviceContext) 
		{ 
			m_pDeviceContext->Release(); 
			m_pDeviceContext = nullptr; 
		}
		if (m_pDevice) 
		{ 
			m_pDevice->Release(); 
			m_pDevice = nullptr; 
		}
	}

} // namespace vega
