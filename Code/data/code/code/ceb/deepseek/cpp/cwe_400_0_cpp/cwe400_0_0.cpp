#include <string>
#include <algorithm>
#include <cctype>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Edge cases: empty pattern or empty content
    if (pattern.empty()) {
        // An empty pattern is considered to be found in any content
        return true;
    }
    
    if (content.empty()) {
        // If content is empty but pattern is not, pattern cannot be found
        return false;
    }
    
    // Use std::search to find the pattern in the content
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end()
    );
    
    // Return true if pattern was found, false otherwise
    return it != content.end();
}