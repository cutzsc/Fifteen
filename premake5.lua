workspace "Fifteen"
	architecture "x86_64"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fifteen"
	location "Source"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	--staticruntime "on"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")
	pchheader "poorpch.h"
	pchsource "Source/src/poorpch.cpp"

	files {
		"Source/src/**.h",
		"Source/src/**.cpp"
	}

	defines {
		"SFML_STATIC"
	}

	includedirs {
		"Source/src",
		"Source/3rdparty/SFML/include"
	}

	libdirs {
		"Source/3rdparty/SFML/lib"
	}

	links {
		"winmm.lib",
		"opengl32.lib",
		"freetype.lib",
		"gdi32.lib",
		"flac.lib",
		"vorbisenc.lib",
		"vorbisfile.lib",
		"vorbis.lib",
		"ogg.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "PR_DEBUG" }
		runtime "Debug"
		symbols "On"
		links {
			"sfml-system-s-d.lib",
			"sfml-window-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-audio-s-d.lib"
		}

	filter "configurations:Release"
		defines { "PR_RELEASE" }
		runtime "Release"
		optimize "On"
		links {
			"sfml-system-s.lib",
			"sfml-window-s.lib",
			"sfml-graphics-s.lib",
			"sfml-audio-s.lib"
		}