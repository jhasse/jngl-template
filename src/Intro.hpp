#pragma once

#include "engine/ResizeGraphics.hpp"

#include <array>
#include <jngl.hpp>
#include <vector>

class Intro : public jngl::Work {
public:
	Intro();
	void step() override;
	void draw() const override;

private:
	int blink = 255;

	// mutable since we're loading while drawing:
	mutable ResizeGraphics resizeGraphics_;
	mutable std::vector<std::function<jngl::Finally()>> loadingFunctions;
	mutable size_t currentIndex = 0;

	std::array<bool, 4> playersReady{false};
};
