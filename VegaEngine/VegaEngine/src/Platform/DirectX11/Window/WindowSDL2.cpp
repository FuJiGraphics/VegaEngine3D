#include "pch.h"
#include <SDL.h>
#include "Core/Window.h"
#include "WindowSDL2.h"

namespace vega {

	WindowSDL2::WindowSDL2(const WindowSpec& spec)
		: m_Width(spec.Width)
		, m_Height(spec.Height)
		, m_Title(spec.Title)
		, m_IsFullscreen(spec.Fullscreen)
		, m_IsReleased(false)
		, m_Input(nullptr)
		, m_Application(nullptr)
		, m_Hinstance(NULL)
		, m_Hwnd(NULL)
	{
		// Empty
	}

	WindowSDL2::~WindowSDL2()
	{
	}

	bool WindowSDL2::Init()
	{
		return false;
	}

	void WindowSDL2::Release()
	{
	}

	void WindowSDL2::Frame(bool& isRunning)
	{
	}

	inline unsigned int WindowSDL2::GetWidth() const
	{
		return 0;
	}

	inline unsigned int WindowSDL2::GetHeight() const
	{
		return 0;
	}

	inline const std::string& WindowSDL2::GetTitle() const
	{
		// TODO: insert return statement here
	}

	void WindowSDL2::InitWindow()
	{
	}

	void WindowSDL2::ReleaseWindow()
	{

	}

} // namespace vega