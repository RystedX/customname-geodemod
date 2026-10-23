#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init())
            return false;

        auto value = Mod::get()->getSettingValue<std::string>("thename");
        
        // Safely search for the username label and text field child
        if (auto usernameLabel = this->getChildByID("username-label")) {
            // Try querySelector first or safely check children
            if (auto textField = usernameLabel->getChildByType<CCTextFieldTTF>(0)) {
                textField->setString(value.c_str());
            } else if (usernameLabel->getChildrenCount() > 0) {
                if (auto textFieldFallback = typeinfo_cast<CCTextFieldTTF*>(usernameLabel->getChildren()->objectAtIndex(0))) {
                    textFieldFallback->setString(value.c_str());
                }
            }
        }

        return true;
    }
};
