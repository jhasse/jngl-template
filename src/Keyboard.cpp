#include <jngl.hpp>
#include "Keyboard.hpp"

Keyboard::Keyboard(int playerNr) : playerNr(playerNr) {
}

template <class Key> jngl::Vec2 findMovement(Key up, Key down, Key left, Key right) {
	jngl::Vec2 direction;
	if (jngl::keyDown(left)) {
		direction -= jngl::Vec2(1, 0);
	}
	if (jngl::keyDown(right)) {
		direction += jngl::Vec2(1, 0);
	}
	if (jngl::keyDown(up)) {
		direction -= jngl::Vec2(0, 1);
	}
	if (jngl::keyDown(down)) {
		direction += jngl::Vec2(0, 1);
	}
	return direction;
}

jngl::Vec2 Keyboard::getMovement() const {
	// change speed
	jngl::Vec2 direction;
	if (playerNr == 0) {
		direction = findMovement(jngl::key::Up, jngl::key::Down, jngl::key::Left, jngl::key::Right);
	} else if (playerNr == 1) {
		direction = findMovement('w', 's', 'a', 'd');
	} else if (playerNr == 2) {
		direction = findMovement('t', 'g', 'f', 'h');
	} else if (playerNr == 3) {
		direction = findMovement('i', 'k', 'j', 'l');
	}

	if (boost::qvm::mag_sqr(direction) > 1) {
		boost::qvm::normalize(direction);
	}
	return direction;
}
