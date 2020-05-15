#pragma once

#include <box2d/box2d.h>

class ContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact*) override;
	void EndContact(b2Contact*) override;
};
