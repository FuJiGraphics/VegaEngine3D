#pragma once
#include "Defines.h"

namespace vega {

	static class TypeConverter
	{
	public:
		static void Init();

		static KeyType ToVegaKeyType(uint32_t key);
		static MouseButtonType ToVegaMouseButtonType(uint32_t key);

		static uint32_t ToScanCode(KeyType key);
		static uint32_t ToSDLMouseButtonCode(MouseButtonType key);

	private:
		static std::unordered_map<uint32_t, KeyType> s_KeyMap;
		static std::unordered_map<uint32_t, MouseButtonType> s_MouseButtonMap;

		static std::unordered_map<KeyType, uint32_t> s_VegaToScanCodeMap;
		static std::unordered_map<MouseButtonType, uint32_t> s_VegaToSDLMouseButtonMap;

		static bool s_IsInitailized;
	};

} // namespace vega
