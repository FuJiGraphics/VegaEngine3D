#pragma once

namespace vega {

	class IWindow;
	class IRenderContext;

	class ImGuiManager final
	{
	public:
		static void Init(IWindow& window, IRenderContext& context);
		static void Release(IWindow& window, IRenderContext& context);

		static void PollEvent(const SDL_Event& event);
		static void Frame();

		static bool IsFocusUI(const SDL_Event& event);
	};


} // namespace vega
