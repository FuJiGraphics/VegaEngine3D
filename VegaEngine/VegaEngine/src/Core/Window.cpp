#include "pch.h"
#include "Window.h"
#include "Platform/Window/WindowWin32.h"

namespace vega {

	Shared<Window> Window::Create(const WindowSpec& spec)
	{
		switch (spec.Api)
		{
			case WindowAPI::Win32:
				return CreateShared<WindowWin32>(spec);
		}
	}


} // namespace vega
