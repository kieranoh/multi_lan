#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern is empty
    if (pattern.empty()) {
        return false;
    }

    // Use the find method to search for the pattern in the content
    size_t position = content.find(pattern);
    
    // If position is not found, find returns std::string::npos
    return position != std::string::npos;
}