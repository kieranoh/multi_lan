#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern is empty
    if (pattern.empty()) {
        return false; // Return false if the pattern is empty
    }
    
    // Use the find method to search for the pattern in the content
    size_t found = content.find(pattern);
    
    // If the pattern is found, return true, otherwise return false
    return (found != std::string::npos);
}