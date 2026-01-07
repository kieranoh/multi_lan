#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty
    if (user_id.empty()) {
        return ""; // Return empty string if user_id is invalid
    }
    // Construct the query URL by appending user_id to api_url
    return api_url + "/" + user_id;
}