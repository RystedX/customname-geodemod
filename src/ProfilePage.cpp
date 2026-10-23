#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) 
            return false;

        if (!m_usernameLabel) 
            return true;

        // Safely check if it's your own profile using account ID matching
        int currentAccountID = GJAccountManager::get()->m_accountID;
        bool isOwnProfile = ownProfile || (accountID == currentAccountID);

        if (isOwnProfile) {
            auto value = Mod::get()->getSettingValue<std::string>("thename");
            m_usernameLabel->setString(value.c_str());
        }

        return true;
    }

    void loadPageFromUserInfo(GJUserScore* user) {
        ProfilePage::loadPageFromUserInfo(user);

        if (!m_usernameLabel || !user) 
            return;

        // Safely check using m_ownProfile and matching account IDs
        int currentAccountID = GJAccountManager::get()->m_accountID;
        bool isOwnProfile = m_ownProfile || (user->m_accountID == currentAccountID);

        if (isOwnProfile) {
            auto value = Mod::get()->getSettingValue<std::string>("thename");
            m_usernameLabel->setString(value.c_str());
        }
    }
};
