project "VegaEngine"
	location "VegaEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	systemversion "latest"

pchheader "pch.h"
pchsource "%{wks.location}/VegaEngine/VegaEngine/src/pch.cpp"

targetdir(binDir)
objdir(binIntDir)

files
{
	"%{prj.name}/**.cpp",
	"%{prj.name}/**.hpp",
	"%{prj.name}/**.h",
}

includedirs
{
	"%{IncludeDir.VegaEngine}/",
	"%{IncludeDir.Workspace}/",
	"%{IncludeDir.SDL2}/",
}

libdirs
{
	"%{LibraryDir.SDL2}/",
}

prebuildcommands 
{
}

links
{
	"d3d11.lib",
	"D3DCompiler.lib",
	"dxgi.lib",
	"dxguid.lib",
	"SDL2.lib",
}

filter "system:Windows"
linkoptions { "/IGNORE:4006" }
buildoptions { "/bigobj" }

defines
{
	"VG_PLATFORM_WINDOWS",
}

filter "configurations:Debug"
	defines "VG_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "VG_RELEASE"
	runtime "Release"
	optimize "On"
