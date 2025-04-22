workspace "ZenithAudio"
	architecture "x86_64"
	startproject "ZenithAudio-Examples"

	configurations { "Debug", "Release", "Dist" }
	
	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs
	{
		"%{prj.name}/src",
	}

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