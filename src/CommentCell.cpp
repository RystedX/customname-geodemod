#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>

using namespace geode::prelude;

class $modify(CommentCell) {
    void loadFromComment(GJComment* p0) {
        CommentCell::loadFromComment(p0);

        if (!p0) return;

        std::string accountname = GJAccountManager::get()->m_username;
        if (accountname.empty()) return;

        auto value = Mod::get()->getSettingValue<std::string>("thename");

        // 1. Try to find profile comment label directly
        if (auto profilename = this->querySelector("username-label")) {
            if (auto label = typeinfo_cast<CCLabelBMFont*>(profilename)) {
                if (accountname == label->getString()) {
                    label->setString(value.c_str());
                }
                return;
            }
        }

        // 2. Search for level comment username button safely
        auto usernameBtn = this->querySelector("main-menu > user-menu > username-menu > username-button");
        if (!usernameBtn) {
            // Fallback for direct node search if nested hierarchy differs
            usernameBtn = this->querySelector("username-button");
        }

        if (usernameBtn) {
            // Check label inside CCMenuItemLabel / CCMenuItemSpriteExtra
            CCLabelBMFont* label = nullptr;

            if (auto menuItem = typeinfo_cast<CCMenuItemLabel*>(usernameBtn)) {
                label = typeinfo_cast<CCLabelBMFont*>(menuItem->getLabel());
            } else if (usernameBtn->getChildrenCount() > 0) {
                label = typeinfo_cast<CCLabelBMFont*>(usernameBtn->getChildren()->objectAtIndex(0));
            }

            if (label && accountname == label->getString()) {
                label->setString(value.c_str());
            }
        }
    }
};
