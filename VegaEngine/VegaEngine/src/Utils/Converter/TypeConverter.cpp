#include "pch.h"
#include "TypeConverter.h"
#include <SDL.h>

namespace vega {

	std::unordered_map<uint32_t, KeyType> TypeConverter::s_KeyMap;
	std::unordered_map<uint32_t, MouseButtonType> TypeConverter::s_MouseButtonMap;
	std::unordered_map<KeyType, uint32_t> TypeConverter::s_VegaToScanCodeMap;
	std::unordered_map<MouseButtonType, uint32_t> TypeConverter::s_VegaToSDLMouseButtonMap;
	bool TypeConverter::s_IsInitailized = false;

	void TypeConverter::Init()
	{
		if (s_IsInitailized)
			return;

		// 알파벳 키 (소문자 ASCII)
		for (char c = 'a'; c <= 'z'; ++c)
		{
			KeyType vegaKey = static_cast<KeyType>(static_cast<int>(KeyType::A) + (c - 'a'));
			uint32_t ascii = static_cast<uint32_t>(c);
			s_KeyMap[ascii] = vegaKey;
			s_VegaToScanCodeMap[vegaKey] = static_cast<SDL_Scancode>(SDL_SCANCODE_A + (c - 'a'));
		}

		// 숫자 키 (ASCII 0~9)
		for (char n = '0'; n <= '9'; ++n)
		{
			KeyType vegaKey = static_cast<KeyType>(static_cast<int>(KeyType::Num0) + (n - '0'));
			uint32_t ascii = static_cast<uint32_t>(n);
			s_KeyMap[ascii] = vegaKey;
			s_VegaToScanCodeMap[vegaKey] = static_cast<SDL_Scancode>(SDL_SCANCODE_0 + (n - '0'));
		}

		// 특수 키
		s_KeyMap[SDLK_LCTRL] = KeyType::LControl;
		s_VegaToScanCodeMap[KeyType::LControl] = SDL_SCANCODE_LCTRL;

		s_KeyMap[SDLK_RCTRL] = KeyType::RControl;
		s_VegaToScanCodeMap[KeyType::RControl] = SDL_SCANCODE_RCTRL;

		s_KeyMap[SDLK_LALT] = KeyType::LAlt;
		s_VegaToScanCodeMap[KeyType::LAlt] = SDL_SCANCODE_LALT;

		s_KeyMap[SDLK_RALT] = KeyType::RAlt;
		s_VegaToScanCodeMap[KeyType::RAlt] = SDL_SCANCODE_RALT;

		s_KeyMap[SDLK_LSHIFT] = KeyType::LShift;
		s_VegaToScanCodeMap[KeyType::LShift] = SDL_SCANCODE_LSHIFT;

		s_KeyMap[SDLK_RSHIFT] = KeyType::RShift;
		s_VegaToScanCodeMap[KeyType::RShift] = SDL_SCANCODE_RSHIFT;

		s_KeyMap[SDLK_RETURN] = KeyType::Enter;
		s_VegaToScanCodeMap[KeyType::Enter] = SDL_SCANCODE_RETURN;

		s_KeyMap[SDLK_ESCAPE] = KeyType::Escape;
		s_VegaToScanCodeMap[KeyType::Escape] = SDL_SCANCODE_ESCAPE;

		s_KeyMap[SDLK_TAB] = KeyType::Tab;
		s_VegaToScanCodeMap[KeyType::Tab] = SDL_SCANCODE_TAB;

		s_KeyMap[SDLK_BACKSPACE] = KeyType::Backspace;
		s_VegaToScanCodeMap[KeyType::Backspace] = SDL_SCANCODE_BACKSPACE;

		s_KeyMap[SDLK_SPACE] = KeyType::Space;
		s_VegaToScanCodeMap[KeyType::Space] = SDL_SCANCODE_SPACE;

		s_KeyMap[SDLK_INSERT] = KeyType::Insert;
		s_VegaToScanCodeMap[KeyType::Insert] = SDL_SCANCODE_INSERT;

		s_KeyMap[SDLK_DELETE] = KeyType::Delete;
		s_VegaToScanCodeMap[KeyType::Delete] = SDL_SCANCODE_DELETE;

		s_KeyMap[SDLK_HOME] = KeyType::Home;
		s_VegaToScanCodeMap[KeyType::Home] = SDL_SCANCODE_HOME;

		s_KeyMap[SDLK_END] = KeyType::End;
		s_VegaToScanCodeMap[KeyType::End] = SDL_SCANCODE_END;

		s_KeyMap[SDLK_PAGEUP] = KeyType::PageUp;
		s_VegaToScanCodeMap[KeyType::PageUp] = SDL_SCANCODE_PAGEUP;

		s_KeyMap[SDLK_PAGEDOWN] = KeyType::PageDown;
		s_VegaToScanCodeMap[KeyType::PageDown] = SDL_SCANCODE_PAGEDOWN;

		// 방향키
		s_KeyMap[SDLK_LEFT] = KeyType::Left;
		s_VegaToScanCodeMap[KeyType::Left] = SDL_SCANCODE_LEFT;

		s_KeyMap[SDLK_RIGHT] = KeyType::Right;
		s_VegaToScanCodeMap[KeyType::Right] = SDL_SCANCODE_RIGHT;

		s_KeyMap[SDLK_UP] = KeyType::Up;
		s_VegaToScanCodeMap[KeyType::Up] = SDL_SCANCODE_UP;

		s_KeyMap[SDLK_DOWN] = KeyType::Down;
		s_VegaToScanCodeMap[KeyType::Down] = SDL_SCANCODE_DOWN;

		// Function Keys
		for (int i = 0; i <= 11; ++i)
		{
			KeyType vegaKey = static_cast<KeyType>(static_cast<int>(KeyType::F1) + i);
			SDL_Keycode sdlKey = SDLK_F1 + i;
			SDL_Scancode scan = static_cast<SDL_Scancode>(static_cast<int>(SDL_SCANCODE_F1) + i);

			s_KeyMap[sdlKey] = vegaKey;
			s_VegaToScanCodeMap[vegaKey] = scan;
		}

		// 마우스 버튼
		s_MouseButtonMap[SDL_BUTTON_LEFT] = MouseButtonType::Left;
		s_MouseButtonMap[SDL_BUTTON_MIDDLE] = MouseButtonType::Middle;
		s_MouseButtonMap[SDL_BUTTON_RIGHT] = MouseButtonType::Right;
		s_MouseButtonMap[SDL_BUTTON_X1] = MouseButtonType::XButton1;
		s_MouseButtonMap[SDL_BUTTON_X2] = MouseButtonType::XButton2;

		s_VegaToSDLMouseButtonMap[MouseButtonType::Left] = SDL_BUTTON_LEFT;
		s_VegaToSDLMouseButtonMap[MouseButtonType::Middle] = SDL_BUTTON_MIDDLE;
		s_VegaToSDLMouseButtonMap[MouseButtonType::Right] = SDL_BUTTON_RIGHT;
		s_VegaToSDLMouseButtonMap[MouseButtonType::XButton1] = SDL_BUTTON_X1;
		s_VegaToSDLMouseButtonMap[MouseButtonType::XButton2] = SDL_BUTTON_X2;

		s_IsInitailized = true;
	}

	KeyType TypeConverter::ToVegaKeyType(uint32_t key)
	{
		auto it = s_KeyMap.find(key);
		if (it != s_KeyMap.end())
			return it->second;

		return KeyType::Unknown;
	}

	MouseButtonType TypeConverter::ToVegaMouseButtonType(uint32_t key)
	{
		auto it = s_MouseButtonMap.find(key);
		if (it != s_MouseButtonMap.end())
			return it->second;

		return MouseButtonType::Left;
	}

	uint32_t TypeConverter::ToScanCode(KeyType key)
	{
		auto it = s_VegaToScanCodeMap.find(key);
		if (it != s_VegaToScanCodeMap.end())
			return it->second;

		return SDL_SCANCODE_UNKNOWN;
	}

	uint32_t TypeConverter::ToSDLMouseButtonCode(MouseButtonType key)
	{
		auto it = s_VegaToSDLMouseButtonMap.find(key);
		if (it != s_VegaToSDLMouseButtonMap.end())
			return it->second;

		return SDLK_UNKNOWN;
	}

} // namespace vega
