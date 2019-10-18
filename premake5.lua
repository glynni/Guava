-- indents in this file dont actually matter, just for readability

workspace "Guava"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

-- output directory for later resuse, this uses premake TAGS -> "%{some.tag}" 
-- in this case it probably results in "Debug-Windows-x64"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Guava"
	location "Guava"	-- root/Guava/...
	kind "SharedLib"	-- build a dll
	language "C++"		-- programming language

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	-- use .h files and .cpp files inside the src directory
	files { 
	"%{prj.name}/src/**.h", 
	"%{prj.name}/src/**.cpp" } 

	-- include paths
	includedirs { 
	"%{prj.name}/vendor/spdlog/include" }

	-- everything underneath this filter only applies to windows builds & all configurations
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
		"GUAVA_PLATFORM_WINDOWS",
		"GUAVA_BUILD_DLL" }

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
	"Guava/vendor/spdlog/include",
	"Guava/src" }

	-- link to Guava project
	links { "Guava" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
		"GUAVA_PLATFORM_WINDOWS" }

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