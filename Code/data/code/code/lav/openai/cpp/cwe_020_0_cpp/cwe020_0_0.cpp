#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regex to match the target URL against the provided domain
    std::regex domain_regex("^(https://)(.*\\.)?" + domain + "(/.*)?$");

    // Check if the target matches the domain
    if (std::regex_match(target, domain_regex)) {
        return target; // Return the original target URL if it's within the domain
    } else {
        return "https://" + domain; // Otherwise, return the domain URL
    }
}