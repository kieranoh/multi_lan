#include <string>
#include <algorithm>
#include <cctype>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Patroia hutsa bada, ez dago bilatzeko ezer
    if (pattern.empty()) {
        return false;
    }
    
    // Edukia hutsa bada, patroia ezin da aurkitu
    if (content.empty()) {
        return false;
    }
    
    // Patroiaren luzera edukia baino handiagoa bada, ezin da aurkitu
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // Bilaketa lineala (std::string::find erabiliz)
    // find metodoak std::string::npos itzultzen du patroia ez badu aurkitzen
    return content.find(pattern) != std::string::npos;
}