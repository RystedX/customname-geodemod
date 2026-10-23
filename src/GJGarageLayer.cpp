#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(GJGarageLayer) {
	bool init() {
	    if (!GJGarageLayer::init())
            return false;

		auto value = Mod::get()->getSettingValue<std::string>("thename");
		
		// Safely search for the username label and its text field child to prevent crashes
		if (auto usernameLabel = this->getChildByID("username-label")) {
			if (usernameLabel->getChildrenCount() > 0) {
				if (auto textField = typeinfo_cast<CCTextFieldTTF*>(usernameLabel->getChildren()->objectAtIndex(0))) {
					textField->setString(value.c_str());
				}
			}
		}

		return true;
	}
};
