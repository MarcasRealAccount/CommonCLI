#include "ANSI/ANSI.h"
#include "ANSI/Graphics.h"
#include "ANSI/Terminals/CMD.h"
#include "ANSI/Terminals/ExpectEverything.h"
#include "ANSI/Terminals/Unsupported.h"
#include "Premake/Defines.h"

#include <cstdlib>

#include <iostream>

#if PREMAKE_IS_SYSTEM_WINDOWS
	#include <Windows.h>
	#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
		#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
	#endif
#endif

namespace ANSI {
	ANSI ANSI::s_Ansi;

	ANSI::ANSI() {
		setup();

		if constexpr (Premake::s_IsSystemWindows) {
			m_TerminalName   = "cmd";
			m_Implementation = new Terminals::CMD();
		} else if constexpr (Premake::s_IsSystemUnix) {
			m_TerminalName   = std::getenv("TERM");
			m_Implementation = new Terminals::ExpectEverything();
		} else {
			m_TerminalName   = "";
			m_Implementation = new Terminals::Unsupported();
		}
	}

	ANSI::~ANSI() {
		restore();
		delete m_Implementation;
	}

#if PREMAKE_IS_SYSTEM_WINDOWS
	static HANDLE stdoutHandle;
	static DWORD defaultMode;
#endif

	void setup() {
#if PREMAKE_IS_SYSTEM_WINDOWS
		stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (stdoutHandle == INVALID_HANDLE_VALUE)
			return;

		DWORD mode;
		if (!GetConsoleMode(stdoutHandle, &mode))
			return;

		defaultMode = mode;
		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(stdoutHandle, mode);
#endif
	}

	void restore() {
		std::cout << GraphicsReset;

#if PREMAKE_IS_SYSTEM_WINDOWS
		if (stdoutHandle == INVALID_HANDLE_VALUE)
			return;

		SetConsoleMode(stdoutHandle, defaultMode);
#endif
	}
} // namespace ANSI