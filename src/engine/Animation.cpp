#include "Animation.hpp"

#include "../Game.hpp"

#include <fstream>
#include <iomanip>

Animation::Animation(const std::string& foldername, const bool repeat)
: foldername_(foldername + "/"), finished_(false), stepsLeft_(0), repeat(repeat) {
	std::string filename(jngl::getPrefix() + foldername_ + "frames.txt");
	std::ifstream fin(filename);
	if (!fin) {
		throw std::runtime_error(std::string("Couldn't open ") + filename);
	}
	while (fin) {
		std::string temp;
		std::getline(fin, temp);
		std::stringstream line(temp);
		std::string command;
		line >> command;
		if (command == "fps") {
			double fps;
			line >> fps;
			const int stepsPerSecond = jngl::getStepsPerSecond();
			stepsPerFrame_ = static_cast<int>(stepsPerSecond / fps);
			stepsLeft_ = stepsPerFrame_;
		}
		if (command == "numberOfFrames") {
			line >> numberOfFrames;
		}
	}
	assert(numberOfFrames > 0 && stepsPerFrame_ > 0 && stepsLeft_ > 0);
}

template <class T> int numDigits(T number) {
	int digits = 0;
	if (number < 0) digits = 1; // remove this line if '-' counts as a digit
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}

std::string Animation::CreateFilename(int frameNumber) const {
	std::stringstream filename;
	filename << foldername_ << std::setfill('0') << std::setw(numDigits(numberOfFrames))
	         << frameNumber % numberOfFrames;
	return filename.str();
}

void Animation::draw() const {
	if (!finished_) {
		const auto f = CreateFilename(currentFrame);
		jngl::draw(f, position.x - jngl::getWidth(f) / 2.,
		           position.y - jngl::getHeight(f) / 2.);
	}
}

void Animation::setFrame(unsigned int frameNr) {
	currentFrame = frameNr;
}

void Animation::setPosition(jngl::Vec2 position) {
	this->position = position;
}

bool Animation::step() {
	--stepsLeft_;
	if (stepsLeft_ <= 0) {
		stepsLeft_ = stepsPerFrame_;
		++currentFrame;
		if (currentFrame >= numberOfFrames) {
			finished_ = !repeat;
			if (finished_) {
				return true;
			}
		}
	}
	return false;
}

bool Animation::Finished() {
	return finished_;
}

void Animation::reset() {
	finished_ = false;
	stepsLeft_ = stepsPerFrame_;
	currentFrame = 0;
}