#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>

using namespace geode::prelude;

class $modify(LevelCell) {
    void loadCustomLevelCell() {
        LevelCell::loadCustomLevelCell();
        
        auto mainObj = this->getChildByID("main-layer");
        if (mainObj == nullptr) {
            log::warn("Failed to move on because \"main-layer\" doesnt exist LevelCell");
            return;
        }
        
        auto menuStuff = mainObj->getChildByID("main-menu");
        if (menuStuff == nullptr) {
            log::warn("Failed to move on because \"main-menu\" doesnt exist in \"main-layer\" -> LevelCell");
            return;
        }
        
        auto creatorname = menuStuff->getChildByID("creator-name");
        if (creatorname == nullptr) {
            log::warn("Failed to move on because \"creator-name\" doesnt exist in \"main-menu\" -> \"main-layer\" -> LevelCell");
            return;
        }
        
        if (creatorname->getChildrenCount() == 0) {
            return;
        }
        
        auto obj = typeinfo_cast<CCLabelBMFont*>(creatorname->getChildren()->objectAtIndex(0));
        if (obj == nullptr) {
            return;
        }
        
        std::string objString(obj->getString());
        std::string accountname = GJAccountManager::get()->m_username;
        
        if (this->m_compactView) {
            if (accountname == objString) {
                auto value = Mod::get()->getSettingValue<std::string>("thename");
                obj->setString(value.c_str());
            }
        } else {
            // Ensure string length is enough for substr to avoid out-of-range exceptions
            if (objString.length() >= 3) {
                if (accountname == objString.substr(3, -1)) {
                    auto value = Mod::get()->getSettingValue<std::string>("thename");
                    obj->setString(fmt::format("By {}", value).c_str());
                }
            }
        }
	}
};
