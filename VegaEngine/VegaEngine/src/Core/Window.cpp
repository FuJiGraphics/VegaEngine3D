#include "pch.h"
#include "Window.h"
#include "Platform/DirectX11/Window/WindowDX11.h"

namespace vega {

	static Shared<Window> s_TargetMessageHandler = nullptr;

	Shared<Window> Window::Create(const WindowSpec& spec)
	{
		switch (spec.Api)
		{
			case WindowAPI::Win32:
				return CreateShared<WindowDX11>(spec);
		}
	}


} // namespace vega
