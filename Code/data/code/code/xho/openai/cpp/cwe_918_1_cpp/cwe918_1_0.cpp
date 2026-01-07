#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or invalid
    if (user_id.empty()) {
        return ""; // Return an empty string if user_id is empty
    }
    
    // Construct the query URL by concatenating api_url and user_id
    return api_url + "/" + user_id; // Return the constructed URL
}