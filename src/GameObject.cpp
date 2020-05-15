#include "GameObject.hpp"

#include "constants.hpp"

#include <box2d/box2d.h>
#include <jngl.hpp>

jngl::Vec2 GameObject::getPosition() const {
	return meterToPixel(body->GetPosition());
}

void GameObject::setPosition(const jngl::Vec2 position) {
	const auto transform = body->GetTransform();
	body->SetTransform(pixelToMeter(position), transform.q.GetAngle());
}

void GameObject::setRotation(const float radian) {
	const auto transform = body->GetTransform();
	body->SetTransform(transform.p, radian);
}

float GameObject::getRotation() const {
	return body->GetTransform().q.GetAngle();
}

int GameObject::getAmount() const {
	return 0;
}

double GameObject::getZIndex() const {
	return getPosition().y;
}

void GameObject::onContact(GameObject* other) {
}

void GameObject::checkOutOfScreen() {
	jngl::Vec2 pos = getPosition();
	float width = jngl::getScreenWidth() / 2.f;
	float height = jngl::getScreenHeight() / 2.f;

	if (pos.x < -width) {
		setPosition({ width, pos.y });
	}
	if (pos.x > width) {
		setPosition({ -width, pos.y });
	}
	if (pos.y > height) {
		setPosition({ pos.x, -height });
	}
	if (pos.y < -height) {
		setPosition({ pos.x, height });
	}
}

void GameObject::createFixtureFromShape(const b2Shape& shape) {
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.filter.categoryBits = FILTER_CATEGORY_SOLID_OBJECT;
	fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
	body->SetGravityScale(1);
}
