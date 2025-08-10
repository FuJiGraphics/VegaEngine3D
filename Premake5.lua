workspace "Solution"
	startproject "VegaEditor"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
	binDir = "%{wks.location}/Build/bin/" .. outputDir
	binIntDir = "%{wks.location}/Build/bin-int/" .. outputDir

	-- Include Directories
	IncludeDir = {}
	IncludeDir["VegaEngine"]	= "%{wks.location}/VegaEngine/VegaEngine/src"
	IncludeDir["VegaEditor"]	= "%{wks.location}/VegaEditor/VegaEditor/src"
	IncludeDir["Workspace"]		= "%{wks.location}/Workspace/Workspace"
	IncludeDir["Entt"]			= "%{wks.location}/Vendor/entt/include"
	IncludeDir["SDL2"]			= "%{wks.location}/Vendor/sdl2/include"
	IncludeDir["Imgui"]			= "%{wks.location}/Vendor/imgui/include"

	-- Library Path
	LibraryDir = {}
	LibraryDir["VegaEngine"]	= "%{wks.location}/Build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/VegaEngine"
	LibraryDir["SDL2"]			= "%{wks.location}/Vendor/sdl2/lib/%{cfg.architecture}"
	LibraryDir["Imgui"]			= "%{wks.location}/Vendor/imgui/lib/%{cfg.buildcfg}"

	-- DLL Working Directories
	WorkingDir = {}
	WorkingDir["Root"]			= "%{wks.location}"

	group "Dependencies"
		include "vendor/premake5"
		include "vendor/imgui"
	group ""

include "VegaEngine"
include "VegaEditor"
include "Workspace"

