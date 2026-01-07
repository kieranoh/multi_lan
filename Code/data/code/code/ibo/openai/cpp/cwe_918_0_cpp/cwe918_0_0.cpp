#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain prefix is valid
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-") != std::string::npos) {
        return "https://" + domain;
    }
    
    // Construct the full URL
    return "https://" + subdomain_prefix + "." + domain;
}