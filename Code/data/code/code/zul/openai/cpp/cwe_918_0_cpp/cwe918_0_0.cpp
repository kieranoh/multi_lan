#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain_prefix is empty or contains invalid characters.
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        // If invalid or empty, return the domain itself as the URL
        return "https://" + domain;
    }
    
    // Construct the full URL using the valid subdomain_prefix
    return "https://" + subdomain_prefix + "." + domain;
}