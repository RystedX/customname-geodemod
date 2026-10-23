#include "utils.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* p0, bool p1) {
        if (!LevelInfoLayer::init(p0, p1))
            return false;

        // Safely check and retrieve the creator-info-menu and creator-name nodes
        auto menuNode = this->querySelector("creator-info-menu");
        if (!menuNode) {
            menuNode = this->getChildByID("creator-info-menu");
        }
        if (menuNode == nullptr) {
            return true;
        }

        auto creatorNameNode = menuNode->getChildByID("creator-name");
        if (creatorNameNode == nullptr || creatorNameNode->getChildrenCount() == 0) {
            return true;
        }

        auto obj = typeinfo_cast<CCLabelBMFont*>(creatorNameNode->getChildren()->objectAtIndex(0));
        if (obj == nullptr) {
            return true;
        }
        
        std::string objString(obj->getString());
        std::string accountname = GJAccountManager::get()->m_username;

        // Ensure string length is enough for substr to avoid out-of-range exceptions
        if (objString.length() < 3) {
            return true;
        }

        // Fixed: Removed unsafe '-1' parameter from substr
        if (accountname != objString.substr(3)) {
            return true;
        }

        auto value = Mod::get()->getSettingValue<std::string>("thename");
        obj->setString(fmt::format("By {}", value).c_str());

        return true;
    }
};
