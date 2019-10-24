-- Indents in this file dont actually matter, just for readability

workspace "Guava"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

-- Output directory for later resuse, this uses premake TAGS -> "%{some.tag}" 
-- In this case it probably results in "Debug-Windows-x64"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{prj.name}/vendor/glfw/include"
IncludeDir["GLAD"] = "%{prj.name}/vendor/GLAD/include"
IncludeDir["GLM"] = "%{prj.name}/vendor/glm/glm"

-- Include another premake5.lua file
include "Guava/vendor/glfw"
include "Guava/vendor/GLAD"

project "Guava"
	location "Guava"	-- root/Guava/...
	kind "SharedLib"	-- Build a dll
	language "C++"		-- Programming language

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	-- Use .h files and .cpp files inside the src directory
	files { 
	"%{prj.name}/src/**.h", 
	"%{prj.name}/src/**.cpp" } 

	-- Include paths
	includedirs { 
	"%{prj.name}/src/",
	"%{prj.name}/vendor/spdlog/include",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.GLAD}",
	"%{IncludeDir.GLM}" }

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
		"GUAVA_PLATFORM_WINDOWS",
		"GUAVA_BUILD_DLL",
		"GLFW_INCLUDE_NONE" }

		-- Copy DLL to Sandbox after building
		postbuildcommands {
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")}

	-- Debug builds on all platforms/systems
	filter "configurations:Debug"
		defines "GUAVA_DEBUG"
		symbols "On"

	-- Release Builds on all platforms/systems
	filter "configurations:Release"
		defines "GUAVA_RELEASE"
		optimize "On"

	-- Dist Builds on all platforms/systems
	filter "configurations:Dist"
		defines "GUAVA_DIST"
		optimize "On"

	-- Windows release builds
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	files { 
	"%{prj.name}/src/**.h", 
	"%{prj.name}/src/**.cpp" } 

	includedirs { 
	"Guava/vendor/GLFW/include",
	"Guava/vendor/spdlog/include",
	"Guava/src" }

	-- Link to Guava project
	links { "Guava" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
		"GUAVA_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "GUAVA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GUAVA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GUAVA_DIST"
		optimize "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"