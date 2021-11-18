#include "Premake/Defines.h"

#include <sstream>

namespace Premake {
	std::ostream& printPremakeConfigFlags(std::ostream& stream, const PremakeConfigFlags& flags) {
		std::ostringstream str;
		bool hasAppended = false;

		PremakeConfigFlags value = flags;
		if (value == PremakeConfigFlag::Unknown) {
			str << "Unknown";
		} else {
			if ((value & PremakeConfigFlag::Debug) == PremakeConfigFlag::Debug) {
				str << "Debug";
				value &= ~PremakeConfigFlag::Debug;
				hasAppended = true;
			}
			if ((value & PremakeConfigFlag::Dist) == PremakeConfigFlag::Dist) {
				if (hasAppended)
					str << " | ";
				str << "Dist";
				value &= ~PremakeConfigFlag::Dist;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0) {
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}

	std::ostream& printPremakeSystemFlags(std::ostream& stream, const PremakeSystemFlags& flags) {
		std::ostringstream str;
		bool hasAppended = false;

		PremakeSystemFlags value = flags;
		if (value == PremakeSystemFlag::Unknown) {
			str << "Unknown";
		} else {
			if ((value & PremakeSystemFlag::Windows) == PremakeSystemFlag::Windows) {
				str << "Windows";
				value &= ~PremakeSystemFlag::Windows;
				hasAppended = true;
			}
			if ((value & PremakeSystemFlag::Macosx) == PremakeSystemFlag::Macosx) {
				if (hasAppended)
					str << " | ";
				str << "Macosx";
				value &= ~PremakeSystemFlag::Macosx;
				hasAppended = true;
			}
			if ((value & PremakeSystemFlag::Linux) == PremakeSystemFlag::Linux) {
				if (hasAppended)
					str << " | ";
				str << "Linux";
				value &= ~PremakeSystemFlag::Linux;
				hasAppended = true;
			}
			if ((value & PremakeSystemFlag::Unix) == PremakeSystemFlag::Unix) {
				if (hasAppended)
					str << " | ";
				str << "Unix";
				value &= ~PremakeSystemFlag::Unix;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0) {
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}

	std::ostream& printPremakeToolsetFlags(std::ostream& stream, const PremakeToolsetFlags& flags) {
		std::ostringstream str;
		bool hasAppended = false;

		PremakeToolsetFlags value = flags;
		if (value == PremakeToolsetFlag::Unknown) {
			str << "Unknown";
		} else {
			if ((value & PremakeToolsetFlag::MSVC) == PremakeToolsetFlag::MSVC) {
				str << "MSVC";
				value &= ~PremakeToolsetFlag::MSVC;
				hasAppended = true;
			}
			if ((value & PremakeToolsetFlag::Clang) == PremakeToolsetFlag::Clang) {
				if (hasAppended)
					str << " | ";
				str << "Clang";
				value &= ~PremakeToolsetFlag::Clang;
				hasAppended = true;
			}
			if ((value & PremakeToolsetFlag::GCC) == PremakeToolsetFlag::GCC) {
				if (hasAppended)
					str << " | ";
				str << "GCC";
				value &= ~PremakeToolsetFlag::GCC;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0) {
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}

	std::ostream& printPremakePlatformFlags(std::ostream& stream, const PremakePlatformFlags& flags) {
		std::ostringstream str;
		bool hasAppended = false;

		PremakePlatformFlags value = flags;
		if (value == PremakePlatformFlag::Unknown) {
			str << "Unknown";
		} else {
			if ((value & PremakePlatformFlag::X86) == PremakePlatformFlag::X86) {
				str << "X86";
				value &= ~PremakePlatformFlag::X86;
				hasAppended = true;
			}
			if ((value & PremakePlatformFlag::AMD64) == PremakePlatformFlag::AMD64) {
				if (hasAppended)
					str << " | ";
				str << "AMD64";
				value &= ~PremakePlatformFlag::AMD64;
				hasAppended = true;
			}
			if ((value & PremakePlatformFlag::ARM32) == PremakePlatformFlag::ARM32) {
				if (hasAppended)
					str << " | ";
				str << "ARM32";
				value &= ~PremakePlatformFlag::ARM32;
				hasAppended = true;
			}
			if ((value & PremakePlatformFlag::ARM64) == PremakePlatformFlag::ARM64) {
				if (hasAppended)
					str << " | ";
				str << "ARM64";
				value &= ~PremakePlatformFlag::ARM64;
				hasAppended = true;
			}
			if (static_cast<std::uint16_t>(value) != 0) {
				if (hasAppended)
					str << " | ";
				str << value;
			}
		}

		return stream << str.str();
	}
} // namespace Premake
