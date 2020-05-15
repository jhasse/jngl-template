#include "Sprite.hpp"

#include "../Game.hpp"
#include "effects/Effect.hpp"

Sprite::Sprite(jngl::Vec2 position) : position(position) {
}

Sprite::Sprite(const std::string& filename, jngl::Vec2 position) : position(position) {
	setFilename(filename);
}

Sprite::~Sprite() = default;

void Sprite::add() {
	std::weak_ptr<Game> work = std::dynamic_pointer_cast<Game>(jngl::getWork());
	auto p = work.lock();
	if (p) {
		p->addSprite(this);
	}
	removeFunction = [work](Sprite* s) {
		auto p = work.lock();
		if (p) {
			p->removeSprite(s);
		}
	};
}

void Sprite::remove() {
	removeFunction(this);
}

void Sprite::step() {
	for (const auto& effect : effects) {
		effect->step();
	}
	if (!needToRemove.empty()) {
		for (auto& effect : needToRemove) {
			const auto it = std::find_if(effects.begin(), effects.end(),
			                             [effect](const auto& p) { return p.get() == effect; });
			if (it != effects.end()) {
				effects.erase(it);
			}
		}
		needToRemove.clear();
	}
}

void Sprite::draw() const {
	jngl::pushMatrix();
	jngl::translate(position);
	for (const auto& effect : effects) {
		effect->beginDraw();
	}
	drawSelf();
	for (const auto& effect : effects) {
		effect->endDraw();
	}
	jngl::popMatrix();
}

void Sprite::drawSelf() const {
	sprite->draw();
}

void Sprite::addEffect(std::unique_ptr<Effect> e) {
	e->setSprite(this);
	effects.emplace_back(std::move(e));
}

void Sprite::removeEffect(Effect* e) {
	needToRemove.insert(e);
}

void Sprite::setFilename(const std::string& f) {
	sprite.reset(new jngl::Sprite("gfx/" + f));
}

void Sprite::setPos(jngl::Vec2 p) {
	position = p;
}

jngl::Vec2 Sprite::getPos() const {
	return position;
}

void Sprite::removeEffects() {
	effects.clear();
}

void Sprite::setRemoveFunction(std::function<void(Sprite*)> f) {
	removeFunction = std::move(f);
}
