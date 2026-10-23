#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) 
            return false;

        if (!m_usernameLabel) 
            return true;

        std::string accountName = GJAccountManager::get()->m_username;
        std::string labelName = m_usernameLabel->getString();

        // Properly compare std::strings instead of raw pointers
        auto isOwnProfile = (ownProfile || (accountName == labelName));

        log::info("Custom Name Profile Page: GJ Account Name is \"{}\". The Label Name is \"{}\". ownprofile is \"{}\". Combined ownprofile is \"{}\"", accountName, labelName, ownProfile, isOwnProfile);

        if (isOwnProfile) {
            auto value = Mod::get()->getSettingValue<std::string>("thename");
            m_usernameLabel->setString(value.c_str());
        }

        return true;
    }

    void loadPageFromUserInfo(GJUserScore* user) {
        ProfilePage::loadPageFromUserInfo(user);

        if (!m_usernameLabel) 
            return;

        std::string accountName = GJAccountManager::get()->m_username;
        std::string labelName = m_usernameLabel->getString();

        // Properly compare std::strings instead of raw pointers
        auto isOwnProfile = (m_ownProfile || (accountName == labelName));
        
        log::info("Custom Name Profile Page: GJ Account Name is \"{}\". The Label Name is \"{}\". m_ownProfile is \"{}\". Combined ownprofile is \"{}\"", accountName, labelName, m_ownProfile, isOwnProfile);

        if (isOwnProfile) {
            auto value = Mod::get()->getSettingValue<std::string>("thename");
            m_usernameLabel->setString(value.c_str());
        }
    }
};
