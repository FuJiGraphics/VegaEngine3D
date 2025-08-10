#pragma once

namespace vega {

	class ImGuiManager final
	{
	public:
		static void Init(void* nativeWindow);
		static void Release();

		static void Frame();
		static void Render();
	};


} // namespace vega
