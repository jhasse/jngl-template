#include "Player.hpp"

#include "constants.hpp"
#include "Gamepad.hpp"
#include "Keyboard.hpp"

#include <cmath>

Player::Player(b2World& world, const jngl::Vec2 position) {
	b2BodyDef bodyDef;
	bodyDef.position = pixelToMeter(position);
	bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&bodyDef);
	body->SetGravityScale(0);
	body->SetUserData(static_cast<GameObject*>(this));
	body->SetLinearDamping(10.f);

	b2CircleShape shape = b2CircleShape();
	shape.m_radius = 12 / PIXEL_PER_METER;
	createFixtureFromShape(shape);
}

Player::~Player() {
	if (body) {
		body->GetWorld()->DestroyBody(body);
	}
}

bool Player::step() {
	return false;
}

void Player::draw() const {
	sprite.draw();
}

void Player::onContact(GameObject* other) {
}
