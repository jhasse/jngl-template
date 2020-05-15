#include "constants.hpp"

#include <box2d/box2d.h>
#include <jngl.hpp>

jngl::Vec2 meterToPixel(const b2Vec2& v) {
	return {v.x * PIXEL_PER_METER, v.y * PIXEL_PER_METER};
}

b2Vec2 pixelToMeter(const jngl::Vec2& v) {
	return b2Vec2(v.x / PIXEL_PER_METER, v.y / PIXEL_PER_METER);
}

float pixelToMeter(const float v) {
	return v / PIXEL_PER_METER;
}

void printCentered(const std::string& text, double x, double y) {
	jngl::print(text, static_cast<int>((x - jngl::getTextWidth(text) / 2)),
	            static_cast<int>(y) - jngl::getFontSize() / 2);
}
