#include "pch.h"
#include "IWindow.h"
#include "Platform/DirectX11/Window/WindowSDL2.h"

namespace vega {

	static Shared<IWindow> s_TargetMessageHandler = nullptr;

	Shared<IWindow> IWindow::Create(const WindowSpec& spec)
	{
		switch (spec.Api)
		{
			case WindowAPI::SDL2:
				return CreateShared<WindowSDL2>(spec);
		}
	}

} // namespace vega
