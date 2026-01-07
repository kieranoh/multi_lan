#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain prefix is empty or contains invalid characters
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-") != std::string::npos) {
        return "https://" + domain; // Return the domain itself if subdomain is invalid
    }

    // Construct the URL using the provided subdomain prefix
    return "https://" + subdomain_prefix + '.' + domain;
}