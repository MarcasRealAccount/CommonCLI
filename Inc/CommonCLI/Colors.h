#pragma once

#include "ANSI/Graphics.h"

namespace CommonCLI::Colors {
	static constexpr ANSI::GraphicsForegroundColor Info      = { 127, 255, 255 };
	static constexpr ANSI::GraphicsForegroundColor Warn      = { 255, 127, 0 };
	static constexpr ANSI::GraphicsForegroundColor Error     = { 255, 30, 30 };
	static constexpr ANSI::GraphicsForegroundColor Usage     = { 127, 255, 63 };
	static constexpr ANSI::GraphicsForegroundColor Help      = { 127, 255, 255 };
	static constexpr ANSI::GraphicsForegroundColor Arg       = { 255, 255, 66 };
	static constexpr ANSI::GraphicsForegroundColor Note      = { 255, 255, 0 };
	static constexpr ANSI::GraphicsForegroundColor NoteLabel = { 255, 63, 63 };
} // namespace CommonCLI::Colors