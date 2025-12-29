#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Tarkistetaan, että kuvio ja sisältö eivät ole tyhjät
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Käytetään std::string::find -metodia kuvion etsimiseen sisällöstä
    size_t found = content.find(pattern);
    
    // Palautetaan true, jos kuvio löytyy, muuten false
    return (found != std::string::npos);
}