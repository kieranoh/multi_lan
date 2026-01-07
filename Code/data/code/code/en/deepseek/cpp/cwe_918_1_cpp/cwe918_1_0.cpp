#include <string>
#include <algorithm>
#include <cctype>

/**
Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return an empty string so that no query will be made.
Examples:
- get_url_for_query("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") returns an empty string

@param api_url: The API URL to query user info.
@param user_id: The user ID to query.

@return The URL for query. If the user ID is empty or invalid, return an empty string.
*/
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty
    if (user_id.empty()) {
        return "";
    }
    
    // Check if user_id contains only valid characters (alphanumeric and common safe URL characters)
    // Common safe characters for URL path segments: A-Z, a-z, 0-9, -, _, ., ~
    // We'll also allow % for percent-encoded characters
    auto is_valid_char = [](char c) -> bool {
        return std::isalnum(static_cast<unsigned char>(c)) ||
               c == '-' || c == '_' || c == '.' || c == '~' || c == '%';
    };
    
    // Check if all characters in user_id are valid
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), is_valid_char);
    
    if (!is_valid) {
        return "";
    }
    
    // Construct the query URL
    // Ensure there's exactly one '/' between api_url and user_id
    std::string result = api_url;
    
    // Remove trailing slashes from api_url
    while (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Append user_id with a single slash
    result += "/" + user_id;
    
    return result;
}