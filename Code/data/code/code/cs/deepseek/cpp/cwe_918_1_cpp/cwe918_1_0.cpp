#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or invalid
    if (user_id.empty()) {
        return "";
    }
    
    // Check if user_id contains only alphanumeric characters
    // (common requirement for user IDs in URLs)
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c));
    });
    
    if (!is_valid) {
        return "";
    }
    
    // Construct the query URL
    // Ensure there's no trailing slash in api_url before appending
    std::string result = api_url;
    
    // Remove trailing slash if present
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Append user_id
    result += "/" + user_id;
    
    return result;
}