#pragma once

#include <string>

#include <vector>



class Utils final {

private:

    bool gamelaunch;

    std::string displayNameModID;

    static Utils* sharedutils;

public:

    Utils();



    static Utils* get();



    bool const& getLaunch() const {return gamelaunch;}

    void afterLaunch() {gamelaunch = false;}

    bool dnInstalled();

    bool nameTransferred();

    bool nameTransfered();

    std::vector<std::string> splitString(const std::string& s, const std::string& delimiter);

};
