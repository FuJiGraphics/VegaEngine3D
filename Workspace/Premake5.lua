project "Workspace"
	location "Workspace"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	systemversion "latest"

-- pchheader "etc/pch.h"
-- pchsource "%{wks.location}/%{prj.name}/etc/pch.cpp"

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
	"%{IncludeDir.Workspace}/",
	"%{IncludeDir.VegaEngine}/src/",
}

libdirs
{

}

links
{
}

prebuildcommands 
{ 
	
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
