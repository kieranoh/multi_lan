#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Tarkistetaan, että sekä kuvio että sisältö eivät ole tyhjiä
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // Tarkistetaan, että kuvio ei ole pidempi kuin sisältö
    if (pattern.length() > content.length()) {
        return false;
    }
    
    try {
        // Yritetään etsiä kuviota sisällöstä käyttäen regex:iä
        // pattern voi sisältää regex-metamerkkejä, joten käytämme regex-kirjastoa
        std::regex regexPattern(pattern);
        
        // Etsitään ensimmäinen osuma
        std::smatch match;
        bool found = std::regex_search(content, match, regexPattern);
        
        return found;
        
    } catch (const std::regex_error& e) {
        // Jos pattern ei ole kelvollinen regex, yritetään yksinkertaista merkkijonohakua
        try {
            // Käytetään std::string::find yksinkertaiseen merkkijonohakuun
            size_t foundPos = content.find(pattern);
            return foundPos != std::string::npos;
            
        } catch (...) {
            // Jos jokin menee pieleen myös yksinkertaisessa haussa
            return false;
        }
    } catch (...) {
        // Jos jokin muu menee pieleen
        return false;
    }
}