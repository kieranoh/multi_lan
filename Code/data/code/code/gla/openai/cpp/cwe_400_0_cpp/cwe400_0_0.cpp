#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Find the position of the pattern in the content
    size_t position = content.find(pattern);
    
    // If the position is not found, return false
    if (position == std::string::npos) {
        return false;
    }
    
    // If the position is found, return true
    return true;
}