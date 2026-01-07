#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain prefix is empty or invalid
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-") != std::string::npos) {
        // Return the domain itself if subdomain is empty or invalid
        return "https://" + domain;
    }
    // Return the constructed URL with the subdomain
    return "https://" + subdomain_prefix + "." + domain;
}