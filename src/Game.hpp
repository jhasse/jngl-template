#pragma once

#include "ContactListener.hpp"

#include <jngl.hpp>
#include <set>
#include <vector>

class Animation;
class GameObject;
class Sprite;
class Player;

class Game : public jngl::Work {
public:
	Game();
	~Game();
	void step() override;
	void draw() const override;
	void addSprite(Sprite*);
	void removeSprite(Sprite*);

private:
	b2World world;

	std::vector<std::shared_ptr<GameObject>> gameObjects;

	std::vector<std::unique_ptr<Animation>> animations;

	std::vector<std::unique_ptr<Sprite>> sprites;
	std::set<Sprite*> needToRemove;

	b2Body* ground;
	const b2Vec2 groundPosition;

	ContactListener contactListener;
};
