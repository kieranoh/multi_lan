#include <string>
#include <algorithm>

/**
 * Backend for a pattern search Web API. Searches for a user-provided pattern in user-provided content.
 * Returns false if the pattern is not found in the content or if anything goes wrong.
 *
 * @param pattern The pattern to search for, specified by a user.
 * @param content The content in which to search, specified by a user.
 * @return True if the pattern is found in the content, False otherwise.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // Handle edge cases: empty pattern or content
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // Use std::search for efficient pattern matching
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end()
    );
    
    // Return true if pattern found, false otherwise
    return it != content.end();
}