#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
    static void onModify(auto& self) {
        self.setHookPriority("MenuLayer::init", -2); // fix with BetterMenu
    }
    
    bool init() {
        if (!MenuLayer::init())
            return false;

        // Get the setting value
        auto value = Mod::get()->getSettingValue<std::string>("thename");
        
        // Safely search for the node to prevent crashes if it doesn't exist
        if (auto usernameLabel = this->getChildByID("player-username")) {
            if (auto label = typeinfo_cast<CCLabelBMFont*>(usernameLabel)) {
                label->setString(value.c_str());
            }
        }
        
        return true;
    }
};
