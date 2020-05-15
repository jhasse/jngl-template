#pragma once

#include <functional>
#include <jngl/Vec2.hpp>
#include <memory>
#include <set>
#include <vector>

class Work;
class Effect;

namespace jngl {
class Sprite;
}

class Sprite {
public:
	Sprite(jngl::Vec2);
	Sprite(const std::string& filename, jngl::Vec2 = jngl::Vec2(0, 0));
	virtual ~Sprite();
	virtual void step();
	virtual void draw() const;
	virtual void addEffect(std::unique_ptr<Effect>);
	virtual void removeEffect(Effect*);
	virtual void removeEffects();
	jngl::Vec2 getPos() const;
	virtual void setPos(jngl::Vec2);
	void add();
	void remove();
	void setFilename(const std::string&);
	void setRemoveFunction(std::function<void(Sprite*)>);

protected:
	virtual void drawSelf() const;

	jngl::Vec2 position;
	std::vector<std::unique_ptr<Effect>> effects;

private:
	std::shared_ptr<jngl::Sprite> sprite;
	std::set<Effect*> needToRemove;
	std::function<void(Sprite*)> removeFunction;
};
