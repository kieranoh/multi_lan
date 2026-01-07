#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regular expression to match the domain in the target URL
    std::regex domain_regex("https?://([^/]+)");
    std::smatch match;

    if (std::regex_search(target, match, domain_regex)) {
        std::string target_domain = match[1];

        // Check if the target domain contains the specified domain
        if (target_domain == domain || target_domain.ends_with("." + domain)) {
            return target; // Return the original target if it matches the domain
        }
    }

    // If the target URL does not match the domain, redirect to the base domain with https
    return "https://" + domain;
}