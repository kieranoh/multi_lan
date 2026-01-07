#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Regular expression to validate subdomain
    std::regex subdomain_regex("^[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*$");
    
    // Check if subdomain_prefix is valid
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain;
    }

    return "https://" + subdomain_prefix + "." + domain;
}