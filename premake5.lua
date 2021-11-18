workspace("CommonCLI")
	configurations({ "Debug", "Release", "Dist" })
	platforms({ "x86", "x64", "arm", "arm64" })
	
	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("Off")
	
	flags("MultiProcessorCompile")

	filter("configurations:Debug")
		defines({ "PREMAKE_CONFIG=PREMAKE_CONFIG_DEBUG" })
		optimize("Off")
		symbols("On")

	filter("configurations:Release")
		defines({ "PREMAKE_CONFIG=PREMAKE_CONFIG_RELEASE" })
		optimize("Full")
		symbols("On")

	filter("configurations:Dist")
		defines({ "PREMAKE_CONFIG=PREMAKE_CONFIG_DIST" })
		optimize("Full")
		symbols("Off")

	filter("system:windows")
		toolset("msc")
		defines({
			"PREMAKE_SYSTEM=PREMAKE_SYSTEM_WINDOWS",
			"NOMINMAX", -- Windows.h disables
			"WIN32_LEAN_AND_MEAN",
			"_CRT_SECURE_NO_WARNINGS"
		})

	filter("system:macosx")
		defines({ "PREMAKE_SYSTEM=PREMAKE_SYSTEM_MACOSX" })

	filter("system:linux")
		defines({ "PREMAKE_SYSTEM=PREMAKE_SYSTEM_LINUX" })

	filter("toolset:msc")
		defines({ "PREMAKE_TOOLSET=PREMAKE_TOOLSET_MSVC" })

	filter("toolset:clang")
		defines({ "PREMAKE_TOOLSET=PREMAKE_TOOLSET_CLANG" })

	filter("toolset:gcc")
		defines({ "PREMAKE_TOOLSET=PREMAKE_TOOLSET_GCC" })

	filter("platforms:x86")
		defines({ "PREMAKE_PLATFORM=PREMAKE_PLATFORM_X86" })

	filter("platforms:x64")
		defines({ "PREMAKE_PLATFORM=PREMAKE_PLATFORM_AMD64" })

	filter("platforms:arm")
		defines({ "PREMAKE_PLATFORM=PREMAKE_PLATFORM_ARM32" })

	filter("platforms:arm64")
		defines({ "PREMAKE_PLATFORM=PREMAKE_PLATFORM_ARM64" })

	filter({})

	startproject("TestCLI")
	
	project("CommonCLI")
		location("%{wks.location}/")
		kind("StaticLib")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/")
		objdir("%{wks.location}/Bin/Int-%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		debugdir("%{wks.location}/")

		includedirs({
			"%{prj.location}/Inc/",
			"%{prj.location}/Src/"
		})

		files({
			"%{prj.location}/Inc/**",
			"%{prj.location}/Src/**"
		})

	project("TestCLI")
		location("%{wks.location}/Test/")
		kind("ConsoleApp")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/")
		objdir("%{wks.location}/Bin/Int-%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		debugdir("%{wks.location}/Test/")

		links({ "CommonCLI" })

		sysincludedirs({ "%{wks.location}/Inc/" })

		includedirs({ "%{prj.location}/Src/" })
		files({ "%{prj.location}/Src/**" })