#pragma once

#include "Singleton.hpp"

#include <cereal/cereal.hpp>

class Options : public Singleton<Options> {
public:
	Options();
	void Save() const;

	int windowWidth;
	int windowHeight;
	bool fullscreen = true;

private:
	std::string filename;

	friend class cereal::access;
	template <class Archive> void serialize(Archive& ar) {
		ar & CEREAL_NVP(windowWidth);
		ar & CEREAL_NVP(windowHeight);
		ar & CEREAL_NVP(fullscreen);
	}
};

Options& getOptions(); // Easier access to the singleton
