#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regex to match the domain part in the URL
    std::regex domain_regex("^(https?://)?(www\\.)?(" + domain + "|([^/]+))");
    
    // Check if the target URL matches the given domain
    if (std::regex_search(target, domain_regex)) {
        return target;  // Return the original URL
    } else {
        // Return the domain URL with the same path
        std::size_t pos = target.find("://");
        std::string path = target.substr(target.find('/', pos + 3)); // Extract path after domain
        return "https://" + domain + path; // Construct new URL
    }
}