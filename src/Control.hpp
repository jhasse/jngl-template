#pragma once

#include <jngl/Vec2.hpp>

class Control {
public:
	virtual ~Control() = default;

	virtual jngl::Vec2 getMovement() const = 0;

	virtual void vibrate();
};
