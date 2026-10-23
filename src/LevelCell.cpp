#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>

using namespace geode::prelude;

class $modify(LevelCell) {
    void loadCustomLevelCell() {
        LevelCell::loadCustomLevelCell();
        
        // Safely search using querySelector or sequential getChildByID
        auto creatorname = this->querySelector("main-layer > main-menu > creator-name");
        if (!creatorname) {
            auto mainObj = this->getChildByID("main-layer");
            if (!mainObj) return;
            
            auto menuStuff = mainObj->getChildByID("main-menu");
            if (!menuStuff) return;
            
            creatorname = menuStuff->getChildByID("creator-name");
        }
        
        if (!creatorname || creatorname->getChildrenCount() == 0) {
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
                // Fixed: Removed unsafe '-1' parameter from substr
                if (accountname == objString.substr(3)) {
                    auto value = Mod::get()->getSettingValue<std::string>("thename");
                    obj->setString(fmt::format("By {}", value).c_str());
                }
            }
        }
    }
};
