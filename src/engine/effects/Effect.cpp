#include "Effect.hpp"

Effect::~Effect() = default;

void Effect::setSprite(Sprite* s) {
	sprite = s;
}
