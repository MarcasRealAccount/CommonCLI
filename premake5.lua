require("Premake/Common")

require("Premake/Libs/CommonCLI")

workspace("CommonCLI")
	common:setConfigsAndPlatforms()

	common:addCoreDefines()

	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("Off")
	flags("MultiProcessorCompile")

	startproject("TestCLI")

	project("CommonCLI")
		location("%{wks.location}/")
		warnings("Extra")
		libs.CommonCLI:setup()

	project("TestCLI")
		location("%{wks.location}/Test/")
		kind("ConsoleApp")
		warnings("Extra")

		common:outDirs()
		common:debugDir()

		includedirs({ "%{prj.location}/Src/" })

		libs.CommonCLI:setupDep()

		files({ "%{prj.location}/Src/**" })
