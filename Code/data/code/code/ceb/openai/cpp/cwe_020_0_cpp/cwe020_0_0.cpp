#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Create a regex pattern to match the domain
    std::string pattern = R"(https?://([^/]+)";
    std::regex regex(pattern);
    std::smatch matches;

    // Check if the target matches the regex
    if (std::regex_search(target, matches, regex)) {
        std::string matched_domain = matches[1].str();
        
        // Check if the matched domain ends with the provided domain
        if (matched_domain == domain || matched_domain.ends_with("." + domain)) {
            return target;  // Return the original target URL
        }
    }

    // If the target does not match the domain, return the domain URL
    return "https://" + domain;
}