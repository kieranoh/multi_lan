#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain prefix is empty or invalid
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_of(" ") != std::string::npos) {
        // Return the main domain with HTTPS
        return "https://" + domain;
    }
    
    // Create the full subdomain URL
    return "https://" + subdomain_prefix + "." + domain;
}