#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Comprovar si el patró o el contingut estan buits
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // Utilitzar std::string::find per a una cerca simple
    // Això és eficient i adequat per a la majoria de casos d'ús
    return content.find(pattern) != std::string::npos;
}