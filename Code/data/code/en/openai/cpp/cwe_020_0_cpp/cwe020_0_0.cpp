#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Ensure the domain has the correct format for comparison
    std::string domain_with_protocol = "https://" + domain;

    // Check if the target starts with the domain URL
    if (target.find(domain_with_protocol) == 0) {
        return target; // Return the target URL if it matches the domain
    }

    // Fallback to the domain URL if the target does not match
    return domain_with_protocol;
}