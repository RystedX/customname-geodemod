#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>

using namespace geode::prelude;

class $modify(CommentCell) {
    void loadFromComment(GJComment* p0) {
        CommentCell::loadFromComment(p0);
        
        // Ensure the cell has enough children before accessing index 1 to prevent crashes
        if (this->getChildrenCount() <= 1) {
            return;
        }
        
        auto mainObj = typeinfo_cast<CCLayer*>(this->getChildren()->objectAtIndex(1));
        if (mainObj == nullptr) {
            log::info("Failed to move on because \"the CCLayer in CommentCell (index 1)\" doesnt exist CommentCell");
            return;
        }
        
        auto profilename = typeinfo_cast<CCLabelBMFont*>(mainObj->getChildByID("username-label"));
        // If is profile comment
        if (profilename != nullptr) {
            std::string objString(profilename->getString());
            std::string accountname = GJAccountManager::get()->m_username;
            if (accountname == objString) {
                auto value = Mod::get()->getSettingValue<std::string>("thename");
                profilename->setString(value.c_str());
            }
            return;
        }
        
        // Continue not a profile comment
        auto menuStuff = mainObj->getChildByID("main-menu");
        if (menuStuff == nullptr) {
            log::info("Failed to move on because \"main-menu\" doesn't exist in \"the CCLayer in CommentCell (index 1)\" -> CommentCell");
            return;
        }
        auto userMenu = menuStuff->getChildByID("user-menu");
        if (userMenu == nullptr) {
            log::info("Failed to move on because \"user-menu\" doesn't exist in \"main-menu\" -> \"the CCLayer in CommentCell (index 1)\" -> CommentCell");
            return;
        }
        auto usernameMenu = userMenu->getChildByID("username-menu");
        if (usernameMenu == nullptr) {
            log::info("Failed to move on because \"username-menu\" doesn't exist in \"user-menu\" -> \"main-menu\" -> \"the CCLayer in CommentCell (index 1)\" -> CommentCell");
            return;
        }
        auto creatorname = usernameMenu->getChildByID("username-button");
        if (creatorname == nullptr) {
            log::info("Failed to move on because \"username-button\" doesn't exist in \"username-menu\" -> \"user-menu\" -> \"main-menu\" -> \"the CCLayer in CommentCell (index 1)\" -> CommentCell");
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
        if (accountname == objString) {
            auto value = Mod::get()->getSettingValue<std::string>("thename");
            obj->setString(value.c_str());
        }
    }
};
