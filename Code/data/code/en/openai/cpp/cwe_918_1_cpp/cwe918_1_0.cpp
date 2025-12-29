#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if the user ID is empty or invalid
    if (user_id.empty()) {
        return ""; // Return an empty string if user ID is invalid
    }

    // Construct the query URL by concatenating the API URL and user ID
    return api_url + "/" + user_id;
}