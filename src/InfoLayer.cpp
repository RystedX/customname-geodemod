#include <Geode/Geode.hpp>
#include <Geode/modify/InfoLayer.hpp>

using namespace geode::prelude;

class $modify(InfoLayer) {
    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        if (!InfoLayer::init(p0, p1, p2))
            return false;

        std::string accountname = GJAccountManager::get()->m_username;
        if (accountname.empty()) return true;

        auto value = Mod::get()->getSettingValue<std::string>("thename");

        // 1. Check for profile/level comments title label safely using querySelector
        if (auto profilename = this->querySelector("title-label")) {
            if (auto label = typeinfo_cast<CCLabelBMFont*>(profilename)) {
                std::string objString(label->getString());
                // Ensure it matches the account name length requirement
                if (objString.length() >= accountname.length() && 
                    accountname == objString.substr(0, accountname.length())) {
                    label->setString(fmt::format("{}'s comments", value).c_str());
                }
            }
        }

        // 2. Search for creator button safely
        auto creatorname = this->querySelector("main-menu > creator-button");
        if (!creatorname) {
            creatorname = this->querySelector("creator-button");
        }

        if (creatorname && creatorname->getChildrenCount() > 0) {
            CCLabelBMFont* label = nullptr;

            // Safely extract the label inside the creator button
            if (auto menuItem = typeinfo_cast<CCMenuItemLabel*>(creatorname)) {
                label = typeinfo_cast<CCLabelBMFont*>(menuItem->getLabel());
            } else {
                label = typeinfo_cast<CCLabelBMFont*>(creatorname->getChildren()->objectAtIndex(0));
            }

            if (label) {
                std::string objString(label->getString());
                // Ensure string length is enough to avoid out-of-range exceptions
                if (objString.length() >= 3) {
                    std::string subStr = objString.substr(3); // Fixed: Removed unsafe '-1'
                    if (accountname == subStr) {
                        label->setString(fmt::format("By {}", value).c_str());
                    }
                }
            }
        }

        return true;
    }
};
