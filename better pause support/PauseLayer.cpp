#include "utils.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(PauseLayer) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("PauseLayer::create", -110);
    }

    static PauseLayer* create(bool p0) {
        auto dathing = PauseLayer::create(p0);
        
        if (!Loader::get()->isModLoaded("tpdea.betterpause-Better")) 
            return dathing;

        Mod* betterpause = Loader::get()->getLoadedMod("tpdea.betterpause-Better");
        bool ratingtextsetting = !betterpause->getSettingValue<bool>("disable-rating-plus-label");
        bool ratingiconsetting = !betterpause->getSettingValue<bool>("disable-icon-rating-plus-label");

        auto mainObj = dathing->getChildByID("better-pause-node");
        if (mainObj == nullptr) {
            log::info("Failed to move on because \"better-pause-node\" doesnt exist PauseLayer"); 
            return dathing;
        }
        
        auto creatorname = mainObj->getChildByID("creator-name");
        if (creatorname == nullptr) {
            log::info("Failed to move on because \"creator-name\" doesnt exist in \"better-pause-node\" -> PauseLayer"); 
            return dathing;
        }

        auto obj = typeinfo_cast<CCLabelBMFont*>(creatorname);
        if (obj == nullptr) {
            return dathing;
        }

        std::string objString(obj->getString());
        std::string accountname = GJAccountManager::get()->m_username;

        // Ensure string length is sufficient before substr
        if (objString.length() < 3) {
            return dathing;
        }

        if (accountname == objString.substr(3, accountname.size())) {
            auto value = Mod::get()->getSettingValue<std::string>("thename");
            
            if (ratingtextsetting) {
                auto split = Utils::get()->splitString(objString, " | ");
                if (split.size() > 1) {
                    obj->setString(fmt::format("By {} | {}", value, split[1]).c_str());
                    
                    if (ratingiconsetting && mainObj->getChildrenCount() > 5) {
                        auto iconNode = typeinfo_cast<CCNode*>(mainObj->getChildren()->objectAtIndex(5));
                        if (iconNode != nullptr) {
                            iconNode->setPosition({ 
                                87.f + obj->getContentSize().width * obj->getScale() + 10.f, 
                                cocos2d::CCDirector::sharedDirector()->getWinSize().height - 18.f 
                            });
                        }
                    }
                } else {
                    obj->setString(fmt::format("By {}", value).c_str());
                }
            } else {
                obj->setString(fmt::format("By {}", value).c_str());
            }
        }
        
        return dathing;
	}
};
