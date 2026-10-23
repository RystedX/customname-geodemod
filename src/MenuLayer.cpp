#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("MenuLayer::init", -2); // Fix compatibility with BetterMenu
    }
    
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto value = Mod::get()->getSettingValue<std::string>("thename");
        
        // Search safely using querySelector or checking direct/profile-menu nodes
        CCNode* usernameNode = this->querySelector("profile-menu > player-username");
        if (!usernameNode) {
            usernameNode = this->getChildByID("player-username");
        }

        if (usernameNode) {
            if (auto label = typeinfo_cast<CCLabelBMFont*>(usernameNode)) {
                label->setString(value.c_str());
            }
        }
        
        return true;
    }
};
