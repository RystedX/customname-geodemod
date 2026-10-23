#include <Geode/Geode.hpp>
#include <Geode/modify/InfoLayer.hpp>

using namespace geode::prelude;

class $modify(InfoLayer) {
    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        if (!InfoLayer::init(p0, p1, p2))
            return false;

        // Ensure the layer has children before accessing index 0
        if (this->getChildrenCount() == 0) {
            return true;
        }

        auto mainObj = typeinfo_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
        if (mainObj == nullptr) {
            log::info("Failed to move on because \"the CCLayer in InfoLayer (index 0)\" doesnt exist InfoLayer");
            return true;
        }

        auto profilename = typeinfo_cast<CCLabelBMFont*>(mainObj->getChildByID("title-label"));
        if (profilename != nullptr) {
            std::string objString(profilename->getString());
            std::string accountname = GJAccountManager::get()->m_username;
            if (accountname == objString.substr(0, accountname.length())) {
                auto value = Mod::get()->getSettingValue<std::string>("thename");
                profilename->setString(fmt::format("{}'s comments", value).c_str());
            }
        }

        auto menuStuff = mainObj->getChildByID("main-menu");
        if (menuStuff == nullptr) {
            log::info("Failed to move on because \"main-menu\" doesnt exist in \"the CCLayer in InfoLayer (index 0)\" -> InfoLayer");
            return true;
        }

        auto creatorname = menuStuff->getChildByID("creator-button");
        if (creatorname == nullptr) {
            log::info("Failed to move on because \"creator-button\" doesnt exist in \"main-menu\" -> \"the CCLayer in InfoLayer (index 0)\" -> InfoLayer");
            return true;
        }

        if (creatorname->getChildrenCount() == 0) {
            return true;
        }

        auto obj = typeinfo_cast<CCLabelBMFont*>(creatorname->getChildren()->objectAtIndex(0));
        if (obj == nullptr) {
            return true;
        }

        std::string objString(obj->getString());
        std::string accountname = GJAccountManager::get()->m_username;
        
        // Ensure string length is enough for substr to avoid out-of-range exceptions
        if (objString.length() < 3) {
            return true;
        }

        if (accountname != objString.substr(3, -1)) {
            return true;
        }

        auto value = Mod::get()->getSettingValue<std::string>("thename");
        obj->setString(fmt::format("By {}", value).c_str());

        return true;
	}
};
