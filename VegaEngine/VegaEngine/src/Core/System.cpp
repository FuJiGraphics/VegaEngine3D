#include "pch.h"
#include "System.h"
#include "IWindow.h"
#include "Layer/LayerContainer.h"
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
	}

	void System::Init()
	{
		// Init Window and run
		m_Window->Init();
		
		// Init Input System
		Input::Init(EInputDevice::Windows);

		ImGuiManager::Init(m_Window->GetNativeWindow());
	}

	void System::Release()
	{
		ImGuiManager::Release();
		m_Window->Release();
	}

	void System::Frame()
	{
		m_Window->PollEvent();
		m_Window->Frame();

		ImGuiManager::Frame();
		ImGuiManager::Render();
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
