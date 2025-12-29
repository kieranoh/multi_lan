#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or contains only whitespace characters
    if (user_id.empty()) {
        return "";
    }
    
    // Check if user_id contains only whitespace characters
    bool all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_whitespace) {
        return "";
    }
    
    // Ensure api_url ends with '/' before appending user_id
    std::string result = api_url;
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    result += user_id;
    return result;
}