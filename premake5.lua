-- Indents in this file dont actually matter, just for readability

workspace "Guava"
	architecture "x64"
	configurations { "Debug", "Release" }

-- Output directory for later resuse, this uses premake TAGS -> "%{some.tag}" 
-- In this case it probably results in "Debug-Windows-x64"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{prj.name}/vendor/glfw/include"
IncludeDir["GLAD"] = "%{prj.name}/vendor/GLAD/include"
IncludeDir["GLM"] = "%{prj.name}/vendor/glm/glm"
IncludeDir["STBI"] = "%{prj.name}/vendor/stb_image"
IncludeDir["ASSIMP"] = "%{prj.name}/vendor/assimp-5.0.0/build/include"

-- Include another premake5.lua file
include "Guava/vendor/glfw"
include "Guava/vendor/GLAD"

project "Guava"
	location "Guava"	-- root/Guava/...
	kind "ConsoleApp"	-- Build a console app
	language "C++"		-- Programming language

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Guava/src/pch.cpp"

	-- Use .h files and .cpp files inside the src directory
	files { 
	"%{prj.name}/src/**.h", 
	"%{prj.name}/src/**.cpp",
	"%{IncludeDir.STBI}/**.cpp",
	"%{IncludeDir.STBI}/**.h" } 

	-- Include paths
	includedirs { 
	"%{prj.name}/src/",
	"%{prj.name}/vendor/spdlog/include",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.GLAD}",
	"%{IncludeDir.GLM}",
	"%{IncludeDir.STBI}",
	"%{IncludeDir.ASSIMP}" }

	links
	{
		"GLFW",
		"GLAD"
	}

	-- Everything underneath this filter only applies to windows builds & all configurations
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
		"GLFW_INCLUDE_NONE" }

	-- Debug builds on all platforms/systems
	filter "configurations:Debug"
		defines "GUAVA_DEBUG"
		symbols "On"

	-- Release Builds on all platforms/systems
	filter "configurations:Release"
		defines "GUAVA_RELEASE"
		optimize "On"

	-- Windows release builds
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"