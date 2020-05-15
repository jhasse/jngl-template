#include "init.hpp"

#include "engine/Options.hpp"
#include "constants.hpp"
#include "Intro.hpp"

#include <jngl.hpp>

bool showWindow() {
	const Options& options = getOptions();
	try {
		jngl::hideWindow();
		jngl::showWindow(programDisplayName, options.windowWidth,
		                 options.windowHeight, options.fullscreen,
		                 { 16, 9 }, { 16, 9 });
	}
	catch(std::runtime_error& err) {
		jngl::errorMessage(err.what());
		return false;
	}
	return true;
}

bool init() {
#ifdef NDEBUG
	try {
#endif
		if (jngl::getDesktopHeight() > 640 && !showWindow() && getOptions().fullscreen) {
			// Try again without fullscreen
			getOptions().fullscreen = false;
			showWindow();
		}
		jngl::setAntiAliasing(true);
		jngl::setWork(std::make_shared<Intro>());
#ifdef NDEBUG
	} catch (std::exception& e) {
		jngl::errorMessage(e.what());
		return false;
	}
#endif
	return true;
}
