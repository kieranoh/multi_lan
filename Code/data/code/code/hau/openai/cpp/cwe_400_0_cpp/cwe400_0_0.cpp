#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern is empty or if content is empty
    if (pattern.empty() || content.empty()) {
        return false; // Return false for empty pattern or content
    }

    // Use the find method to search for the pattern in the content
    size_t found = content.find(pattern);
    
    // Return true if the pattern is found, otherwise false
    return (found != std::string::npos);
}