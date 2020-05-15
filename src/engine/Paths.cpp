#include "Paths.hpp"

#include "../constants.hpp"

#include <sstream>

#if defined(__linux__)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif defined(__APPLE__)
#ifndef __IPHONE_OS_VERSION_MIN_REQUIRED
#include <mach-o/dyld.h>
#include <CoreServices/CoreServices.h>
#endif
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#include <windows.h>
#include <shlobj.h>
#endif
#include <jngl.hpp>

#ifndef __IPHONE_OS_VERSION_MIN_REQUIRED
Paths::Paths() {
#if defined(__linux__)
	fs::current_path(fs::path(jngl::getBinaryPath()) / fs::path("../data"));
	std::stringstream path;
	path << getenv("HOME") << "/.config/" << programDisplayName << "/";
	configPath = path.str();
#elif defined(__APPLE__)
	fs::current_path(fs::path(jngl::getBinaryPath()) / fs::path("../data"));

	FSRef ref;
	FSFindFolder(kUserDomain, kApplicationSupportFolderType, kCreateFolder, &ref);
	char path[PATH_MAX];
	FSRefMakePath(&ref, (UInt8*)&path, PATH_MAX);
	fs::path applicationSupportFolder(path);
	applicationSupportFolder /= programDisplayName;
	configPath = applicationSupportFolder.string() + "/";
#else
	auto dataFolder = fs::path(jngl::getBinaryPath()) / fs::path("../data");
	if (!fs::exists(dataFolder)) {
		dataFolder = fs::path(jngl::getBinaryPath()) / fs::path("../../data");
	}
	fs::current_path(dataFolder);

	TCHAR szPath[MAX_PATH];
	if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath))) {
		throw std::runtime_error("Couldn't get %AppData% location!");
	}
	std::stringstream path;
	path << szPath << "/" << programDisplayName << "/";
	configPath = path.str();
#endif
	fs::create_directory(configPath);
#else
Paths::Paths() : configPath(jngl::getConfigPath()) {
#endif
}

std::string Paths::Graphics() {
	return graphics_;
}

std::string Paths::fonts() const {
	return "fonts/";
}

void Paths::setGraphics(const std::string& graphics) {
	graphics_ = graphics;
}

std::string Paths::Config() {
	return configPath;
}

Paths& getPaths() {
	return *Paths::handle();
}

std::string Paths::OriginalGfx() const {
	return originalGfx_;
}

void Paths::setOriginalGfx(const std::string& originalGfx) {
	originalGfx_ = originalGfx;
}
