#include "pch.h"
#include "System.h"
#include "IWindow.h"
#include "Layer/LayerContainer.h"

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
	}

	void System::Release()
	{
		m_Window->Release();
	}

	void System::Frame()
	{
		m_Window->PollEvent();
		m_Window->Frame();
	}

	void System::OnEvent(vega::Event& e)
	{
		FZLOG_INFO(e.ToString());
	}

} // namespace vega
