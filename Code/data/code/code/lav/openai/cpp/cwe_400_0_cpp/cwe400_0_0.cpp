#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Mēģinām atrast paraugu saturā
    if (content.find(pattern) != std::string::npos) {
        return true; // Paraugs ir atrasts
    }
    return false; // Paraugs nav atrasts
}