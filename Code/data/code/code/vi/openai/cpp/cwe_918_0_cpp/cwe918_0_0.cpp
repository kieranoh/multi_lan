#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Regular expression to validate the subdomain
    std::regex subdomain_regex("^[a-zA-Z0-9](-?[a-zA-Z0-9])*$");
    
    // If the subdomain_prefix is empty or invalid, return the base domain as a URL
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain;
    }
    
    // Construct the full URL with the subdomain
    return "https://" + subdomain_prefix + "." + domain;
}