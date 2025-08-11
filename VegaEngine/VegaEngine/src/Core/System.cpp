#include "pch.h"
#include "System.h"
#include "IWindow.h"
#include "Layer/LayerContainer.h"
#include "Graphic/IRenderContext.h"
#include "Platform/DirectX11/ImGui/ImGuiManager.h"

namespace vega {

	System::System(int width, int height, const std::string& title)
	{
		// Generated a Window
		WindowSpec winSpec;
		winSpec.Api = WindowAPI::SDL2;
		winSpec.Fullscreen = false;
		winSpec.Width = width;
		winSpec.Height = height;
		winSpec.Title = title;
		m_Window = IWindow::Create(winSpec);
		m_Window->SetEventCallback(VG_BIND_CALLBACK_FN(System::OnEvent));

		// Generate Rendering Context
		RenderSpec conSpec;
		conSpec.Api = GraphicsAPI::DirectX11;
		m_RenderContext = IRenderContext::Create(conSpec);
	}

	void System::Init()
	{
		m_Window->Init();					
		m_RenderContext->Init(*m_Window);

		Input::Init(EInputDevice::Windows);
		ImGuiManager::Init(*m_Window, *m_RenderContext);
	}

	void System::Release()
	{
		ImGuiManager::Release(*m_Window, *m_RenderContext);
		m_Window->Release();
	}

	void System::Frame()
	{
		m_Window->PollEvent();

		{ // ImGui
			ImGuiManager::Frame();
		}
		// Rendering
		{
			m_RenderContext->Render();
		}

		m_RenderContext->Present();
	}

	void System::OnEvent(vega::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(VG_BIND_CALLBACK_FN(System::OnWindowClose));

		FZLOG_INFO(e.ToString());
	}

	bool System::OnWindowClose(WindowCloseEvent& e)
	{
		ExitProgram();
		return true;
	}

} // namespace vega
