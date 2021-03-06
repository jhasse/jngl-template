#include "Intro.hpp"

#include "constants.hpp"
#include "engine/Fade.hpp"
#include "Game.hpp"

#include <boost/algorithm/string.hpp>
#include <thread>

#include <datafiles.hpp> // generated by CMake

#include <jngl.hpp>

Intro::Intro() {
	std::vector<std::string> files;
	const std::string filesString(GFX_FILES);
	boost::split(files, filesString, boost::is_any_of(";"));
	for (const auto& filename : files) {
		loadingFunctions.emplace_back(
		    [filename]() { return jngl::load(filename.substr(0, filename.find_last_of('.'))); });
	}
}

void Intro::draw() const {
	jngl::setFontSize(10);

	jngl::pushMatrix();
	jngl::translate(0, 150);
	if (currentIndex != loadingFunctions.size()) {
		std::vector<jngl::Finally> loaders;
		for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
			loaders.emplace_back(loadingFunctions[currentIndex]());
			++currentIndex;
			if (currentIndex == loadingFunctions.size()) {
				break;
			}
		}
		printCentered("Loading ...", 0, 0);
	}
	jngl::popMatrix();
}

void Intro::step() {
	if (currentIndex == loadingFunctions.size()) {
		jngl::setWork(std::make_shared<Fade>(std::make_shared<Game>()));
	}
	if (blink > 2 * 255) {
		blink = 0;
	}
}
