workspace "Fifteen"
	architecture "x86_64"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fifteen"
	location "Code"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")
	pchheader "poorpch.h"
	pchsource "Code/src/poorpch.cpp"

	files {
		"Code/src/**.h",
		"Code/src/**.cpp"
	}

	defines {
		"SFML_STATIC"
	}

	includedirs {
		"Code/src",
		"Code/3rdparty/SFML/include"
	}

	libdirs {
		"Code/3rdparty/SFML/lib"
	}

	links {
		"winmm.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "PR_DEBUG" }
		runtime "Debug"
		symbols "On"
		links {
			"sfml-system-s-d.lib",
			"sfml-window-s-d.lib"
		}

	filter "configurations:Release"
		defines { "PR_RELEASE" }
		runtime "Release"
		optimize "On"
		links {
			"sfml-system-s.lib",
			"sfml-window-s.lib"
		}