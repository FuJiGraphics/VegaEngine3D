#pragma once
#include "Defines.h"

namespace vega {

	static class TypeConverter
	{
	public:
		static void Init();

		static KeyType ToVegaKeyType(uint32_t key);
		static MouseButtonType ToVegaMouseButtonType(uint32_t key);

	private:
		static std::unordered_map<uint32_t, KeyType> s_KeyMap;
		static std::unordered_map<uint32_t, MouseButtonType> s_MouseButtonMap;
	};

} // namespace vega
