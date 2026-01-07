#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or invalid
    if (user_id.empty()) {
        return ""; // Return empty string if user_id is empty
    }
    
    // Create and return the complete query URL
    return api_url + "/" + user_id;
}