#pragma once

#include <deque>
#include <string>

class ResizeGraphics {
public:
	ResizeGraphics();
	bool isFinished(float& percentage);

private:
	std::deque<std::string> filesToResize_;
	int originalSize_;
};
