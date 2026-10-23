#include "utils.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

Utils* Utils::sharedutils = nullptr;

Utils* Utils::get() {
    if (sharedutils == nullptr) {
        sharedutils = new (std::nothrow) Utils();
    }

    return sharedutils;
}

bool Utils::dnInstalled() {
    return geode::Loader::get()->isModLoaded(displayNameModID.c_str());
}

bool Utils::nameTransferred() {
    auto loader = geode::Loader::get();
    return loader->isModLoaded(displayNameModID.c_str()) && 
           loader->getLoadedMod(displayNameModID.c_str())->hasSavedValue("nametransferred");
}

// Mantenemos esta por compatibilidad si otro archivo la llama, 
// pero internamente apunta a la misma lógica correcta.
bool Utils::nameTransfered() {
    return nameTransferred();
}

std::vector<std::string> Utils::splitString(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end;
    while ((end = s.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

Utils::Utils() {
    gamelaunch = true;
    displayNameModID = "coopeeo.displaynames";
}
