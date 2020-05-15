#include "Effect.hpp"

class FadeOut : public Effect {
public:
	FadeOut(int speed = 9);
	void step();
	void beginDraw() const;
	void endDraw() const;

private:
	int alpha;
	int speed;
};
