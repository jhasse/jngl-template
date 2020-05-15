#include "Gamepad.hpp"

Gamepad::Gamepad(std::shared_ptr<jngl::Controller> controller, const int playerNr)
: controller(std::move(controller)), playerNr(playerNr) {
}

jngl::Vec2 Gamepad::getMovement() const {
	const jngl::Vec2 dpad(-controller->state(jngl::controller::DpadLeft) +
	                          controller->state(jngl::controller::DpadRight),
	                      -controller->state(jngl::controller::DpadUp) +
	                          controller->state(jngl::controller::DpadDown));
	const jngl::Vec2 sticks(controller->state(jngl::controller::LeftStickX),
	                        -controller->state(jngl::controller::LeftStickY));
	const jngl::Vec2 sum = dpad + sticks;
	if (boost::qvm::mag_sqr(sum) > 1) {
		return boost::qvm::normalized(sum);
	}
	return sum;
}

void Gamepad::vibrate() {
	controller->rumble(0.5f, std::chrono::milliseconds(100));
}
