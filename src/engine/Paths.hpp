#pragma once

#include "Singleton.hpp"

#include <string>

class Paths : public Singleton<Paths> {
public:
	Paths();
	std::string Graphics();
	std::string Config();
	std::string OriginalGfx() const;
	std::string fonts() const;
	void setGraphics(const std::string&);
	void setOriginalGfx(const std::string&);

private:
	std::string configPath; // %AppData% or $HOME/.config
	std::string graphics_;
	std::string originalGfx_;
};

Paths& getPaths();
