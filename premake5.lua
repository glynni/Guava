-- Indents in this file dont actually matter, just for readability

workspace "Guava"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

-- Output directory for later resuse, this uses premake TAGS -> "%{some.tag}" 
-- In this case it probably results in "Debug-Windows-x64"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
	"%{prj.name}/vendor/spdlog/include" }

	-- Everything underneath this filter only applies to windows builds & all configurations
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
		"GUAVA_PLATFORM_WINDOWS",
		"GUAVA_BUILD_DLL" }

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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	} 

	includedirs 
	{ 
		"Guava/vendor/spdlog/include",
		"Guava/src" 
	}

	-- Link to Guava project
	links 
	{ 
		"Guava" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
		"GUAVA_PLATFORM_WINDOWS" 
	}

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

project "GLFW"
	kind "StaticLib"
	language "C"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",
		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
	}
	--[[filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"src/x11_init.c",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_time.c",
			"src/posix_thread.c",
			"src/glx_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c",
			"src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}]]

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files 
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_monitor.c",
			"src/win32_time.c",
			"src/win32_thread.c",
			"src/win32_window.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"