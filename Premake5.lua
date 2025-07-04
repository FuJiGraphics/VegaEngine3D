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

	-- Library Path
	LibraryDir = {}
	LibraryDir["Box2D"]			= "%{wks.location}/Vendor/Box2D/lib"

	-- DLL Working Directories
	WorkingDir = {}
	WorkingDir["Root"]			= "%{wks.location}"

	group "Dependencies"
		include "vendor/premake5"
	group ""

include "VegaEngine"
include "VegaEditor"
include "Workspace"

