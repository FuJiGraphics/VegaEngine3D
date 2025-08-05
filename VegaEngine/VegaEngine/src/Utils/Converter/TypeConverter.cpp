#include "pch.h"
#include "TypeConverter.h"
#include <SDL.h>

namespace vega {

	std::unordered_map<uint32_t, KeyType> TypeConverter::s_KeyMap;
	std::unordered_map<uint32_t, MouseButtonType> TypeConverter::s_MouseButtonMap;
	bool TypeConverter::s_IsInitailized = false;

	void TypeConverter::Init()
	{
		if (s_IsInitailized)
			return;

		// 알파벳 키 (소문자 ASCII)
		for (char c = 'a'; c <= 'z'; ++c)
			s_KeyMap[static_cast<uint32_t>(c)] = static_cast<KeyType>(static_cast<int>(KeyType::A) + (c - 'a'));

		// 숫자 키 (ASCII 0~9)
		for (char n = '0'; n <= '9'; ++n)
			s_KeyMap[static_cast<uint32_t>(n)] = static_cast<KeyType>(static_cast<int>(KeyType::Num0) + (n - '0'));

		// 특수 키
		s_KeyMap[SDLK_LCTRL] = KeyType::LControl;
		s_KeyMap[SDLK_RCTRL] = KeyType::RControl;
		s_KeyMap[SDLK_LALT] = KeyType::LAlt;
		s_KeyMap[SDLK_RALT] = KeyType::RAlt;
		s_KeyMap[SDLK_LSHIFT] = KeyType::LShift;
		s_KeyMap[SDLK_RSHIFT] = KeyType::RShift;
		s_KeyMap[SDLK_LEFTBRACKET] = KeyType::LBracket;
		s_KeyMap[SDLK_RIGHTBRACKET] = KeyType::RBracket;
		s_KeyMap[SDLK_PERIOD] = KeyType::Period;
		s_KeyMap[SDLK_QUOTEDBL] = KeyType::Apostrophe;
		s_KeyMap[SDLK_BACKQUOTE] = KeyType::Grave;
		s_KeyMap[SDLK_EQUALS] = KeyType::Equal;
		s_KeyMap[SDLK_MINUS] = KeyType::Subtract;
		s_KeyMap[SDLK_LESS] = KeyType::Less;
		s_KeyMap[SDLK_GREATER] = KeyType::Greater;
		s_KeyMap[SDLK_SLASH] = KeyType::Slash;
		s_KeyMap[SDLK_COMMA] = KeyType::Comma;
		s_KeyMap[SDLK_BACKSLASH] = KeyType::Backslash;
		s_KeyMap[SDLK_QUOTE] = KeyType::Quote;
		s_KeyMap[SDLK_RETURN] = KeyType::Enter;
		s_KeyMap[SDLK_ESCAPE] = KeyType::Escape;
		s_KeyMap[SDLK_TAB] = KeyType::Tab;
		s_KeyMap[SDLK_BACKSPACE] = KeyType::Backspace;
		s_KeyMap[SDLK_SPACE] = KeyType::Space;
		s_KeyMap[SDLK_INSERT] = KeyType::Insert;
		s_KeyMap[SDLK_HOME] = KeyType::Home;
		s_KeyMap[SDLK_PAGEUP] = KeyType::PageUp;
		s_KeyMap[SDLK_PAGEDOWN] = KeyType::PageDown;
		s_KeyMap[SDLK_DELETE] = KeyType::Delete;
		s_KeyMap[SDLK_END] = KeyType::End;

		// 방향키
		s_KeyMap[SDLK_LEFT] = KeyType::Left;
		s_KeyMap[SDLK_RIGHT] = KeyType::Right;
		s_KeyMap[SDLK_UP] = KeyType::Up;
		s_KeyMap[SDLK_DOWN] = KeyType::Down;

		// Function Keys (F1~F12)
		s_KeyMap[SDLK_F1] = KeyType::F1;
		s_KeyMap[SDLK_F2] = KeyType::F2;
		s_KeyMap[SDLK_F3] = KeyType::F3;
		s_KeyMap[SDLK_F4] = KeyType::F4;
		s_KeyMap[SDLK_F5] = KeyType::F5;
		s_KeyMap[SDLK_F6] = KeyType::F6;
		s_KeyMap[SDLK_F7] = KeyType::F7;
		s_KeyMap[SDLK_F8] = KeyType::F8;
		s_KeyMap[SDLK_F9] = KeyType::F9;
		s_KeyMap[SDLK_F10] = KeyType::F10;
		s_KeyMap[SDLK_F11] = KeyType::F11;
		s_KeyMap[SDLK_F12] = KeyType::F12;

		// 마우스 버튼
		s_MouseButtonMap[SDL_BUTTON_LEFT] = MouseButtonType::Left;
		s_MouseButtonMap[SDL_BUTTON_MIDDLE] = MouseButtonType::Middle;
		s_MouseButtonMap[SDL_BUTTON_RIGHT] = MouseButtonType::Right;

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
		FZLOG_DEBUG("{0}", key);
		auto it = s_MouseButtonMap.find(key);
		if (it != s_MouseButtonMap.end())
			return it->second;

		return MouseButtonType::Left; // 기본값 (또는 Unknown 타입 추가도 가능)
	}

} // namespace vega