#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern is found in the content
    return content.find(pattern) != std::string::npos;
}