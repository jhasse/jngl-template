#include "FadeOut.hpp"

#include "../Sprite.hpp"

#include <jngl.hpp>

FadeOut::FadeOut(int speed) : alpha(255), speed(speed) {
}

void FadeOut::step() {
	if (alpha > speed) {
		alpha -= speed;
	} else {
		sprite->remove();
	}
}

void FadeOut::beginDraw() const {
	jngl::setFontColor(255, 255, 255, alpha);
	jngl::translate(0, -(255 - alpha) / 10.);
}

void FadeOut::endDraw() const {
	jngl::setFontColor(0, 0, 0, alpha);
}
