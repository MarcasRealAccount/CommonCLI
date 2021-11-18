#include "ANSI/Graphics.h"

namespace ANSI {
	std::ostream& GraphicsBold(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsBold(stream);
	}

	std::ostream& GraphicsDim(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDim(stream);
	}

	std::ostream& GraphicsItalic(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsItalic(stream);
	}

	std::ostream& GraphicsUnderline(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsUnderline(stream);
	}

	std::ostream& GraphicsBlink(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsBlink(stream);
	}

	std::ostream& GraphicsInverse(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsInverse(stream);
	}

	std::ostream& GraphicsHide(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsHide(stream);
	}

	std::ostream& GraphicsStrikethrough(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsStrikethrough(stream);
	}

	std::ostream& operator<<(std::ostream& stream, GraphicsForegroundColor color) {
		return ANSI::s_Ansi.getImplementation().GraphicsForegroundColor(color, stream);
	}

	std::ostream& operator<<(std::ostream& stream, GraphicsBackgroundColor color) {
		return ANSI::s_Ansi.getImplementation().GraphicsBackgroundColor(color, stream);
	}

	std::ostream& operator<<(std::ostream& stream, GraphicsUnderlineColor color) {
		return ANSI::s_Ansi.getImplementation().GraphicsUnderlineColor(color, stream);
	}

	std::ostream& GraphicsReset(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsReset(stream);
	}

	std::ostream& GraphicsDisableBold(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableBold(stream);
	}

	std::ostream& GraphicsDisableDim(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableDim(stream);
	}

	std::ostream& GraphicsDisableItalic(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableItalic(stream);
	}

	std::ostream& GraphicsDisableUnderline(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableUnderline(stream);
	}

	std::ostream& GraphicsDisableBlink(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableBlink(stream);
	}

	std::ostream& GraphicsDisableInverse(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableInverse(stream);
	}

	std::ostream& GraphicsReveal(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsReveal(stream);
	}

	std::ostream& GraphicsDisableStrikethrough(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsDisableStrikethrough(stream);
	}

	std::ostream& GraphicsForegroundDefault(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsForegroundDefault(stream);
	}

	std::ostream& GraphicsBackgroundDefault(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsBackgroundDefault(stream);
	}

	std::ostream& GraphicsUnderlineDefault(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().GraphicsUnderlineDefault(stream);
	}

} // namespace ANSI