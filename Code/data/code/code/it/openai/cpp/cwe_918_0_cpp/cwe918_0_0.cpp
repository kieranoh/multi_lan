#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Regex pattern for validating subdomain
    const std::regex subdomain_pattern(R"(^[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?$)");

    // Check if the subdomain_prefix is empty or invalid
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_pattern)) {
        return "https://" + domain; // Return the domain itself if invalid
    }

    // Construct the URL with the valid subdomain prefix
    return "https://" + subdomain_prefix + "." + domain;
}