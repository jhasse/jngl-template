#pragma once

#include "GameObject.hpp"
#include "engine/Animation.hpp"

#include <array>
#include <box2d/box2d.h>
#include <jngl.hpp>
#include <memory>

class b2World;
class Control;
class PunchAction;
class ShootAction;

class Player : public GameObject {
public:
	Player(b2World& world, const jngl::Vec2 position);
	~Player();

	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(Player&&) = delete;

	bool step() override;

	void dash(jngl::Vec2);
	void punsh();
	void shoot();
	void shield();

	void draw() const override;

	void onContact(GameObject*) override;

private:
	jngl::Sprite sprite{"ball"};
};
