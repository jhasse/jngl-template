#pragma once

#include "Control.hpp"

class Keyboard : public Control {
public:
	Keyboard(int playerNr);

	jngl::Vec2 getMovement() const override;

private:
	const int playerNr;
};
