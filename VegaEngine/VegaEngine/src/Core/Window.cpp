#include "pch.h"
#include "Window.h"
#include "Platform/DirectX11/Window/WindowDX11.h"
#include "Platform/DirectX11/Window/WindowSDL2.h"

namespace vega {

	static Shared<Window> s_TargetMessageHandler = nullptr;

	Shared<Window> Window::Create(const WindowSpec& spec)
	{
		switch (spec.Api)
		{
			case WindowAPI::Win32:
				return CreateShared<WindowDX11>(spec);
			case WindowAPI::SDL2:
				return CreateShared<WindowSDL2>(spec);
		}
	}


} // namespace vega
