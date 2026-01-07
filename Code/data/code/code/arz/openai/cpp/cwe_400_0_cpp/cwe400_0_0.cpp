#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check for empty pattern or content
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Search for the pattern in the content
    return content.find(pattern) != std::string::npos;
}