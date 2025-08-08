#include "pch.h"
#include "InputWindows.h"
#include <SDL.h>

namespace vega {

	bool InputWindows::IsKeyDownImpl(KeyType type)
	{
		const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
		SDL_Scancode scan = static_cast<SDL_Scancode>(TypeConverter::ToScanCode(type));
		return keyStates[scan] != 0;
	}

	bool InputWindows::IsMouseClickedImpl(MouseButtonType type)
	{
		bool result = false;
		uint32_t key = TypeConverter::ToSDLMouseButtonCode(type);
		if (key != SDLK_UNKNOWN)
		{
			result = SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(key);
		}
		return result;
	}

	std::pair<int, int> InputWindows::GetMousePosImpl()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return { x, y };
	}

} // namespace vega
