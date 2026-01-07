#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain_prefix is empty or invalid.
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_of(".") == std::string::npos) {
        // If it's empty or invalid, return the domain itself with HTTPS protocol.
        return "https://" + domain;
    }
    
    // Construct the URL with the subdomain and domain.
    return "https://" + subdomain_prefix + "." + domain;
}