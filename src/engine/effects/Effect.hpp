#pragma once

class Sprite;

class Effect {
public:
	virtual ~Effect();
	virtual void step() = 0;
	virtual void beginDraw() const = 0;
	virtual void endDraw() const = 0;
	void setSprite(Sprite*);

protected:
	Sprite* sprite;
};
