#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Controleer of de inhoud of het patroon leeg is
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Zoek naar het patroon in de inhoud
    size_t found = content.find(pattern);
    
    // Als het patroon wordt gevonden, retourneer true, anders false
    return found != std::string::npos;
}