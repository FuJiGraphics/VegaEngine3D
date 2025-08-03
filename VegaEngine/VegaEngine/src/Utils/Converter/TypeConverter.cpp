#include "pch.h"
#include "TypeConverter.h"

namespace vega {

	std::unordered_map<uint32_t, KeyType> TypeConverter::s_KeyMap;
	std::unordered_map<uint32_t, MouseButtonType> TypeConverter::s_MouseButtonMap;

	void TypeConverter::Init()
	{
		// 문자 키 (아스키 기반)
		s_KeyMap[97] = KeyType::A; // SDLK_a
		s_KeyMap[98] = KeyType::B;
		s_KeyMap[99] = KeyType::C;
		s_KeyMap[100] = KeyType::D;
		s_KeyMap[101] = KeyType::E;
		s_KeyMap[102] = KeyType::F;
		s_KeyMap[103] = KeyType::G;
		s_KeyMap[104] = KeyType::H;
		s_KeyMap[105] = KeyType::I;
		s_KeyMap[106] = KeyType::J;
		s_KeyMap[107] = KeyType::K;
		s_KeyMap[108] = KeyType::L;
		s_KeyMap[109] = KeyType::M;
		s_KeyMap[110] = KeyType::N;
		s_KeyMap[111] = KeyType::O;
		s_KeyMap[112] = KeyType::P;
		s_KeyMap[113] = KeyType::Q;
		s_KeyMap[114] = KeyType::R;
		s_KeyMap[115] = KeyType::S;
		s_KeyMap[116] = KeyType::T;
		s_KeyMap[117] = KeyType::U;
		s_KeyMap[118] = KeyType::V;
		s_KeyMap[119] = KeyType::W;
		s_KeyMap[120] = KeyType::X;
		s_KeyMap[121] = KeyType::Y;
		s_KeyMap[122] = KeyType::Z;

		// 숫자 키
		s_KeyMap[48] = KeyType::Num0; // SDLK_0
		s_KeyMap[49] = KeyType::Num1;
		s_KeyMap[50] = KeyType::Num2;
		s_KeyMap[51] = KeyType::Num3;
		s_KeyMap[52] = KeyType::Num4;
		s_KeyMap[53] = KeyType::Num5;
		s_KeyMap[54] = KeyType::Num6;
		s_KeyMap[55] = KeyType::Num7;
		s_KeyMap[56] = KeyType::Num8;
		s_KeyMap[57] = KeyType::Num9;

		// 주요 키 (SDL_Keycode 값은 정수 그대로 사용)
		s_KeyMap[13] = KeyType::Enter;      // SDLK_RETURN
		s_KeyMap[27] = KeyType::Escape;     // SDLK_ESCAPE
		s_KeyMap[9] = KeyType::Tab;			// SDLK_TAB
		s_KeyMap[8] = KeyType::Backspace;	// SDLK_BACKSPACE
		s_KeyMap[32] = KeyType::Space;      // SDLK_SPACE

		// 방향키 (정수 상수 직접 입력)
		s_KeyMap[1073741904] = KeyType::Left;
		s_KeyMap[1073741903] = KeyType::Right;
		s_KeyMap[1073741906] = KeyType::Up;
		s_KeyMap[1073741905] = KeyType::Down;

		s_MouseButtonMap[1] = MouseButtonType::Left;      // SDL_BUTTON_LEFT
		s_MouseButtonMap[2] = MouseButtonType::Middle;    // SDL_BUTTON_MIDDLE
		s_MouseButtonMap[3] = MouseButtonType::Right;     // SDL_BUTTON_RIGHT
		s_MouseButtonMap[4] = MouseButtonType::XButton1;  // SDL_BUTTON_X1
		s_MouseButtonMap[5] = MouseButtonType::XButton2;  // SDL_BUTTON_X2
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

		return MouseButtonType::Left; // 기본값 (또는 Unknown 타입 추가도 가능)
	}

} // namespace vega