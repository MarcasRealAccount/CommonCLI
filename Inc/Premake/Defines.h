#pragma once

#include "Flags.h"

#define PREMAKE_CONFIG_UNKNOWN 0
#define PREMAKE_CONFIG_DEBUG 1
#define PREMAKE_CONFIG_RELEASE 2
#define PREMAKE_CONFIG_DIST 3

#define PREMAKE_SYSTEM_UNKNOWN 0
#define PREMAKE_SYSTEM_WINDOWS 1
#define PREMAKE_SYSTEM_MACOSX 2
#define PREMAKE_SYSTEM_LINUX 3

#define PREMAKE_TOOLSET_UNKNOWN 0
#define PREMAKE_TOOLSET_MSVC 1
#define PREMAKE_TOOLSET_CLANG 2
#define PREMAKE_TOOLSET_GCC 3

#define PREMAKE_PLATFORM_UNKNOWN 0
#define PREMAKE_PLATFORM_X86 1
#define PREMAKE_PLATFORM_AMD64 2
#define PREMAKE_PLATFORM_ARM32 3
#define PREMAKE_PLATFORM_ARM64 4

#define PREMAKE_IS_CONFIG_DEBUG (PREMAKE_CONFIG == PREMAKE_CONFIG_DEBUG)
#define PREMAKE_IS_CONFIG_DIST ((PREMAKE_CONFIG == PREMAKE_CONFIG_RELEASE) || (PREMAKE_CONFIG == PREMAKE_CONFIG_DIST))

#define PREMAKE_IS_SYSTEM_WINDOWS (PREMAKE_SYSTEM == PREMAKE_SYSTEM_WINDOWS)
#define PREMAKE_IS_SYSTEM_MACOSX (PREMAKE_SYSTEM == PREMAKE_SYSTEM_MACOSX)
#define PREMAKE_IS_SYSTEM_LINUX (PREMAKE_SYSTEM == PREMAKE_SYSTEM_LINUX)

#define PREMAKE_IS_TOOLSET_MSVC (PREMAKE_TOOLSET == PREMAKE_TOOLSET_MSVC)
#define PREMAKE_IS_TOOLSET_CLANG (PREMAKE_TOOLSET == PREMAKE_TOOLSET_CLANG)
#define PREMAKE_IS_TOOLSET_GCC (PREMAKE_TOOLSET == PREMAKE_TOOLSET_GCC)

#define PREMAKE_IS_PLATFORM_X86 (PREMAKE_PLATFORM == PREMAKE_PLATFORM_X86)
#define PREMAKE_IS_PLATFORM_AMD64 (PREMAKE_PLATFORM == PREMAKE_PLATFORM_AMD64)
#define PREMAKE_IS_PLATFORM_ARM32 (PREMAKE_PLATFORM == PREMAKE_PLATFORM_ARM32)
#define PREMAKE_IS_PLATFORM_ARM64 (PREMAKE_PLATFORM == PREMAKE_PLATFORM_ARM64)

namespace Premake {
	using PremakeConfigFlags   = Flags<std::uint16_t>;
	using PremakeSystemFlags   = Flags<std::uint16_t>;
	using PremakeToolsetFlags  = Flags<std::uint16_t>;
	using PremakePlatformFlags = Flags<std::uint16_t>;

	std::ostream& printPremakeConfigFlags(std::ostream& stream, const PremakeConfigFlags& flags);
	std::ostream& printPremakeSystemFlags(std::ostream& stream, const PremakeSystemFlags& flags);
	std::ostream& printPremakeToolsetFlags(std::ostream& stream, const PremakeToolsetFlags& flags);
	std::ostream& printPremakePlatformFlags(std::ostream& stream, const PremakePlatformFlags& flags);

	namespace PremakeConfigFlag {
		static constexpr PremakeConfigFlags Unknown = 0;
		static constexpr PremakeConfigFlags Debug   = 1;
		static constexpr PremakeConfigFlags Dist    = 2;
	} // namespace PremakeConfigFlag

	namespace PremakeSystemFlag {
		static constexpr PremakeSystemFlags Unknown = 0;
		static constexpr PremakeSystemFlags Windows = 1;
		static constexpr PremakeSystemFlags Macosx  = 2;
		static constexpr PremakeSystemFlags Linux   = 4;
		static constexpr PremakeSystemFlags Unix    = 8;
	} // namespace PremakeSystemFlag

	namespace PremakeToolsetFlag {
		static constexpr PremakeToolsetFlags Unknown = 0;
		static constexpr PremakeToolsetFlags MSVC    = 1;
		static constexpr PremakeToolsetFlags Clang   = 2;
		static constexpr PremakeToolsetFlags GCC     = 4;
	} // namespace PremakeToolsetFlag

	namespace PremakePlatformFlag {
		static constexpr PremakePlatformFlags Unknown = 0;
		static constexpr PremakePlatformFlags X86     = 1;
		static constexpr PremakePlatformFlags AMD64   = 2;
		static constexpr PremakePlatformFlags ARM32   = 3;
		static constexpr PremakePlatformFlags ARM64   = 4;
	} // namespace PremakePlatformFlag

#if PREMAKE_IS_CONFIG_DEBUG
	static constexpr PremakeConfigFlags s_Config = PremakeConfigFlag::Debug;
	static constexpr bool s_IsConfigDebug        = true;
	static constexpr bool s_IsConfigDist         = false;
#elif PREMAKE_IS_CONFIG_RELEASE
	static constexpr PremakeConfigFlags s_Config     = PremakeConfigFlag::Debug | PremakeConfigFlags::Dist;
	static constexpr bool s_IsConfigDebug            = true;
	static constexpr bool s_IsConfigDist             = true;
#elif PREMAKE_IS_CONFIG_DIST
	static constexpr PremakeConfigFlags s_Config     = PremakeConfigFlag::Dist;
	static constexpr bool s_IsConfigDebug            = false;
	static constexpr bool s_IsConfigDist             = true;
#else
	static constexpr PremakeConfigFlags s_Config     = PremakeConfigFlag::Unknown;
	static constexpr bool s_IsConfigDebug            = false;
	static constexpr bool s_IsConfigDist             = false;
#endif

#if PREMAKE_IS_SYSTEM_WINDOWS
	static constexpr PremakeSystemFlags s_System = PremakeSystemFlag::Windows;
	static constexpr bool s_IsSystemWindows      = true;
	static constexpr bool s_IsSystemMacosx       = false;
	static constexpr bool s_IsSystemLinux        = false;
	static constexpr bool s_IsSystemUnix         = false;
#elif PREMAKE_IS_SYSTEM_MACOSX
	static constexpr PremakeSystemFlags s_System     = PremakeSystemFlag::Macosx | PremakeSystemFlag::Unix;
	static constexpr bool s_IsSystemWindows          = false;
	static constexpr bool s_IsSystemMacosx           = true;
	static constexpr bool s_IsSystemLinux            = false;
	static constexpr bool s_IsSystemUnix             = true;
#elif PREMAKE_IS_SYSTEM_LINUX
	static constexpr PremakeSystemFlags s_System     = PremakeSystemFlag::Linux | PremakeSystemFlag::Unix;
	static constexpr bool s_IsSystemWindows          = false;
	static constexpr bool s_IsSystemMacosx           = false;
	static constexpr bool s_IsSystemLinux            = true;
	static constexpr bool s_IsSystemUnix             = true;
#else
	static constexpr PremakeSystemFlags s_System     = PremakeSystemFlag::Unknown;
	static constexpr bool s_IsSystemWindows          = false;
	static constexpr bool s_IsSystemMacosx           = false;
	static constexpr bool s_IsSystemLinux            = false;
	static constexpr bool s_IsSystemUnix             = false;
#endif

#if PREMAKE_IS_TOOLSET_MSVC
	static constexpr PremakeToolsetFlags s_Toolset = PremakeToolsetFlag::MSVC;
	static constexpr bool s_IsToolsetMSVC          = true;
	static constexpr bool s_IsToolsetClang         = false;
	static constexpr bool s_IsToolsetGCC           = false;
#elif PREMAKE_IS_TOOLSET_CLANG
	static constexpr PremakeToolsetFlags s_Toolset   = PremakeToolsetFlag::Clang;
	static constexpr bool s_IsToolsetMSVC            = false;
	static constexpr bool s_IsToolsetClang           = true;
	static constexpr bool s_IsToolsetGCC             = false;
#elif PREMAKE_IS_TOOLSET_GCC
	static constexpr PremakeToolsetFlags s_Toolset   = PremakeToolsetFlag::GCC;
	static constexpr bool s_IsToolsetMSVC            = false;
	static constexpr bool s_IsToolsetClang           = false;
	static constexpr bool s_IsToolsetGCC             = true;
#else
	static constexpr PremakeToolsetFlags s_Toolset   = PremakeToolsetFlag::Unknown;
	static constexpr bool s_IsToolsetMSVC            = false;
	static constexpr bool s_IsToolsetClang           = false;
	static constexpr bool s_IsToolsetGCC             = false;
#endif

#if PREMAKE_IS_PLATFORM_X86
	static constexpr PremakePlatformFlags s_Platform = PremakePlatformFlag::X86;
	static constexpr bool s_IsPlatformX86            = true;
	static constexpr bool s_IsPlatformAMD64          = false;
	static constexpr bool s_IsPlatformARM32          = false;
	static constexpr bool s_IsPlatformARM64          = false;
#elif PREMAKE_IS_PLATFORM_AMD64
	static constexpr PremakePlatformFlags s_Platform = PremakePlatformFlag::AMD64;
	static constexpr bool s_IsPlatformX86            = false;
	static constexpr bool s_IsPlatformAMD64          = true;
	static constexpr bool s_IsPlatformARM32          = false;
	static constexpr bool s_IsPlatformARM64          = false;
#elif PREMAKE_IS_PLATFORM_ARM32
	static constexpr PremakePlatformFlags s_Platform = PremakePlatformFlag::ARM32;
	static constexpr bool s_IsPlatformX86            = false;
	static constexpr bool s_IsPlatformAMD64          = false;
	static constexpr bool s_IsPlatformARM32          = true;
	static constexpr bool s_IsPlatformARM64          = false;
#elif PREMAKE_IS_PLATFORM_ARM64
	static constexpr PremakePlatformFlags s_Platform = PremakePlatformFlag::ARM64;
	static constexpr bool s_IsPlatformX86            = false;
	static constexpr bool s_IsPlatformAMD64          = false;
	static constexpr bool s_IsPlatformARM32          = false;
	static constexpr bool s_IsPlatformARM64          = true;
#else
	static constexpr PremakePlatformFlags s_Platform = PremakePlatformFlag::Unknown;
	static constexpr bool s_IsPlatformX86            = false;
	static constexpr bool s_IsPlatformAMD64          = false;
	static constexpr bool s_IsPlatformARM32          = false;
	static constexpr bool s_IsPlatformARM64          = false;
#endif
} // namespace Premake