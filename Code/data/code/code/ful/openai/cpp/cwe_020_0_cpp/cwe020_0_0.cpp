#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regex pattern to match the target URL against the domain
    std::regex pattern("https://([a-zA-Z0-9-]+\\.)*" + domain);
    
    // Check if the target URL matches the domain
    if (std::regex_search(target, pattern)) {
        return target; // Return the original target if it matches
    } else {
        return "https://" + domain; // Return the domain URL if it does not match
    }
}