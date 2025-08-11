#include "pch.h"
#include "Core/IWindow.h"
#include "IRenderContext.h"
#include "Platform/DirectX11/Graphic/RenderContextDX11.h"

namespace vega {

	Shared<IRenderContext> IRenderContext::Create(const RenderSpec& spec)
	{
		switch (spec.Api)
		{
			case GraphicsAPI::DirectX11:
				return CreateShared<RenderContextDX11>();
		}
	}

} // namespace vega
