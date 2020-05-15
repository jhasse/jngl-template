#include "ResizeGraphics.hpp"

#include "Paths.hpp"

#include <jngl.hpp>

ResizeGraphics::ResizeGraphics() : originalSize_(360) {
	const std::string origGfx = "gfx/";
	getPaths().setOriginalGfx(origGfx);
	jngl::setScaleFactor(double(jngl::getWindowHeight())/double(originalSize_));
	getPaths().setGraphics(origGfx);
}
