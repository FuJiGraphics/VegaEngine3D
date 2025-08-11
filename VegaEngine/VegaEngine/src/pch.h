#pragma warning(disable : 4006)
#pragma once

// Standards
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <set>
#include <unordered_set>

// window and rendering
#include <SDL.h>
#include <SDL_syswm.h>
#include <d3d11.h>

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_sdl2.h"

// Libraries
#include "Utils/MagicEnum/magic_enum.hpp"

// Events
#include "Core/Events/KeyType.h"
#include "Core/Events/Event.h"
#include "Core/Events/AppEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

// Vega Engine
#include "Core/Pointer.h"
#include "Core/Input/Input.h"
#include "Utils/Log/FZLog.hpp"
#include "Utils/Converter/TypeConverter.h"
