workspace("CommonCLI")
	configurations({ "Debug", "Release", "Dist" })
	platforms({ "x64" })
	
	cppdialect("C++17")
	rtti("Off")
	exceptionhandling("Off")
	
	flags("MultiProcessorCompile")
	defines({ "PREMAKE_SYSTEM_%{cfg.system}" })

	filter("configurations:Debug")
		defines({ "_DEBUG" })
		optimize("Off")
		symbols("On")

	filter("configurations:Release")
		defines({ "_RELEASE" })
		optimize("Full")
		symbols("On")

	filter("configurations:Dist")
		defines({ "_RELEASE" })
		optimize("Full")
		symbols("Off")

	filter("system:windows")
		defines({ "NOMINMAX", "WIN32_LEAN_AND_MEAN", "_CRT_SECURE_NO_WARNINGS" })

	filter({})

	startproject("TestCLI")
	
	project("CommonCLI")
		location("%{wks.location}/")
		kind("StaticLib")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/")
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
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
		objdir("%{wks.location}/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}/")
		debugdir("%{wks.location}/Test/")

		links({ "CommonCLI" })

		sysincludedirs({ "%{wks.location}/Inc/" })

		includedirs({ "%{prj.location}/Src/" })
		files({ "%{prj.location}/Src/**" })