#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regex to match the target URL against the provided domain
    std::string pattern = "https://([a-zA-Z0-9-]+\\.)*" + domain;
    std::regex domain_regex(pattern);

    // Check if the target URL matches the domain regex
    if (std::regex_search(target, domain_regex)) {
        return target; // Return the original target if it matches the domain
    } else {
        return "https://" + domain; // Return the domain URL if it does not match
    }
}