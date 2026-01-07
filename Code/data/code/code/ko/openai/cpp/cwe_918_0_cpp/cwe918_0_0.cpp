#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validate the subdomain prefix
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // Return just the domain if the subdomain is empty or invalid
    }
    
    // Construct the URL with the valid subdomain
    return "https://" + subdomain_prefix + "." + domain;
}