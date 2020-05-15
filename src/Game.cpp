#include "Game.hpp"

#include "constants.hpp"
#include "engine/Sprite.hpp"
#include "Player.hpp"

#include <cmath>
#include <map>

Game::Game()
: world({ 0, 0 /* gravity */ }), groundPosition(pixelToMeter({ 0, GROUND + PIXEL_PER_METER })) {

	world.SetContactListener(&contactListener);

	b2BodyDef bodyDef;
	bodyDef.position = groundPosition;
	bodyDef.type = b2_kinematicBody;
	ground = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(BOUNDS_W / PIXEL_PER_METER, 1);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.filter.categoryBits = FILTER_CATEGORY_SOLID_OBJECT;
	fixtureDef.filter.maskBits = 0xffff;
	ground->CreateFixture(&fixtureDef);

	gameObjects.emplace_back(std::make_shared<Player>(world, jngl::Vec2(0, 0)));
}

Game::~Game() {
	gameObjects.clear();
}

void Game::step() {
	world.Step(1.f / 60.f, 8, 3);

	for (auto it = animations.begin(); it != animations.end(); ++it) {
		if ((*it)->step()) {
			it = animations.erase(it);
			if (it == animations.end()) {
				break;
			}
		}
	}
	for (auto& sprite : sprites) {
		sprite->step();
	}
	for (auto& sprite : needToRemove) {
		sprites.erase(std::remove_if(
		                  sprites.begin(), sprites.end(),
		                  [sprite](const std::unique_ptr<Sprite>& p) { return p.get() == sprite; }),
		              sprites.end());
	}
	needToRemove.clear();

#ifndef NDEBUG
	if (jngl::keyPressed(jngl::key::F5)) {
		jngl::setWork(std::make_shared<Game>());
	}
#endif
}

void Game::draw() const {
	std::multimap<double, GameObject*> orderedByZIndex;
	std::vector<const Player*> players;
	for (const auto& obj : gameObjects) {
		orderedByZIndex.emplace(obj->getZIndex(), obj.get());
		if (const auto player = dynamic_cast<Player*>(obj.get())) {
			players.emplace_back(player);
		}
	}
	for (const auto& gameObject : orderedByZIndex) {
		gameObject.second->draw();
	}

	for (auto& animation : animations) {
		animation->draw();
	}
	for (auto& sprite : sprites) {
		sprite->draw();
	}
}

void Game::addSprite(Sprite* sprite) {
	sprites.emplace_back(sprite);
}

void Game::removeSprite(Sprite* sprite) {
	needToRemove.insert(sprite);
}
