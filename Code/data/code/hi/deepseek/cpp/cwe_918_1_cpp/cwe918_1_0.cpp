#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or invalid
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
    
    // Construct the query URL
    // Ensure there's a single slash between api_url and user_id
    std::string result = api_url;
    
    // Remove trailing slash from api_url if present
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Add user_id with a slash
    result += "/" + user_id;
    
    return result;
}