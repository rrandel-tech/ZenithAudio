workspace "ZenithAudio"
	architecture "x86_64"
	startproject "ZenithAudio-Examples"

	configurations { "Debug", "Release", "Dist" }
	
	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
include "ZenithAudio/vendor/OpenAL-Soft"
include "ZenithAudio/vendor/libogg"
include "ZenithAudio/vendor/Vorbis"
group ""

project "ZenithAudio"
	location "ZenithAudio"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	defines { "_CRT_SECURE_NO_WARNINGS", "AL_LIBTYPE_STATIC" }

	includedirs
	{
		"%{prj.name}/src",
		"ZenithAudio/vendor/OpenAL-Soft/include",
		"ZenithAudio/vendor/OpenAL-Soft/src",
		"ZenithAudio/vendor/OpenAL-Soft/src/common",
		"ZenithAudio/vendor/libogg/include",
		"ZenithAudio/vendor/Vorbis/include",
		"ZenithAudio/vendor/minimp3",
		"ZenithAudio/vendor/miniaudio/include",
	}

	links
	{ "OpenAL-Soft", "Vorbis" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "ZN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZN_DIST"
		runtime "Release"
		optimize "on"

project "ZenithAudio-Examples"
	location "ZenithAudio-Examples"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs { "ZenithAudio/src" }

	links { "ZenithAudio" }

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "ZN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZN_DIST"
		runtime "Release"
		optimize "on"