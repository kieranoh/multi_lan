#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Regular expression to match URLs with the specified domain
    std::regex domain_regex("https://(www\\.)?" + std::regex_replace(domain, std::regex(R"(\.)"), R"(\.)") + "(/.*)?");

    // Check if the target URL matches the domain pattern
    if (std::regex_match(target, domain_regex)) {
        return target; // Return the target URL if it is within the domain
    } else {
        return "https://" + domain; // Fallback to the domain URL
    }
}