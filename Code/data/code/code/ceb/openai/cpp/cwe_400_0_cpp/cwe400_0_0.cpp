#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern exists in the content
    return content.find(pattern) != std::string::npos;
}