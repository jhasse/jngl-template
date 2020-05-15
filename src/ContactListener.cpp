#include "ContactListener.hpp"

#include "GameObject.hpp"

void ContactListener::BeginContact(b2Contact* contact) {
	const auto bodyA = contact->GetFixtureA()->GetBody();
	if (!bodyA) {
		return;
	}
	const auto a = reinterpret_cast<GameObject*>(bodyA->GetUserData());
	if (!a) {
		return;
	}
	const auto bodyB = contact->GetFixtureB()->GetBody();
	if (!bodyB) {
		return;
	}
	const auto b = reinterpret_cast<GameObject*>(bodyB->GetUserData());
	if (!b) {
		return;
	}
	a->onContact(b);
	b->onContact(a);
}

void ContactListener::EndContact(b2Contact*) {
}
