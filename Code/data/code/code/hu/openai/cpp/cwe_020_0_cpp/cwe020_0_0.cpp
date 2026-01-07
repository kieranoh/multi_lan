#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regular expression to match the URL and extract the hostname
    std::regex url_regex(R"(https?://([^/]+))");
    std::smatch match;

    // Check if the target matches the regex
    if (std::regex_search(target, match, url_regex)) {
        // Extract the hostname
        std::string hostname = match[1].str();

        // Check if the hostname ends with the given domain
        if (hostname == domain || hostname.ends_with("." + domain)) {
            return target; // Return the original target URL
        }
    }
    
    // If the target is not in the domain, return the domain URL
    return "https://" + domain;
}