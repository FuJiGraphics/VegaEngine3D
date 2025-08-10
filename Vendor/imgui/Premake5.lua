project "ImGui"
    kind "StaticLib"
    language "C++"

    targetdir ("lib/%{cfg.buildcfg}")
	objdir ("lib/%{cfg.buildcfg}/bin-int")

    files
	{
		"imgui.cpp",
        "imgui_widgets.cpp",
        "imgui_draw.cpp",
        "imgui_tables.cpp",
        "backends/imgui_impl_dx11.cpp",
        "backends/imgui_impl_sdl2.cpp",
	}

    includedirs
    {
        "%{IncludeDir.IMGUI}/",
		"%{IncludeDir.SDL2}/",
    }

	libdirs 
	{
		"%{LibraryDir.SDL2}/",
	}

	links
	{
		"sdl2.lib"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "off"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "off"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
