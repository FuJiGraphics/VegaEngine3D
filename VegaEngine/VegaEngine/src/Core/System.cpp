#include "pch.h"
#include "System.h"
#include "Window.h"
#include "Layer/LayerContainer.h"

namespace vega {

	System::System(int width, int height, const std::string& title)
	{
		// Generated a Window
		WindowSpec winSpec;
		winSpec.Api = WindowAPI::Win32;
		winSpec.Fullscreen = false;
		winSpec.Width = width;
		winSpec.Height = height;
		winSpec.Title = title;
		m_Window = Window::Create(winSpec);

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

	void System::Run()
	{
		m_Window->Frame(m_IsRunning);
	}

} // namespace vega
