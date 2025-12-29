#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern or content is empty
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Use the std::string::find method to search for the pattern in the content
    size_t found = content.find(pattern);
    
    // Return true if the pattern was found, otherwise return false
    return (found != std::string::npos);
}