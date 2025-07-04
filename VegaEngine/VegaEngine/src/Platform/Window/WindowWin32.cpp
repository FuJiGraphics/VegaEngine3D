#include "pch.h"
#include "Core/Window.h"
#include "WindowWin32.h"

namespace vega {

	WindowWin32::WindowWin32(const WindowSpec& spec)
		: m_Width(spec.Width)
		, m_Height(spec.Height)
		, m_Title(spec.Title)
	{
		// Empty
	}

	inline unsigned int WindowWin32::GetWidth() const
	{
		return m_Width;
	}

	inline unsigned int WindowWin32::GetHeight() const
	{
		return m_Height;
	}

	inline const std::string& WindowWin32::GetTitle() const
	{
		return m_Title;
	}

}
