#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if the user_id is empty or invalid
    if (user_id.empty()) {
        return ""; // Return an empty string if user_id is invalid
    }
    
    // Create the query URL by appending the user_id to the api_url
    return api_url + "/" + user_id;
}