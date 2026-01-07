#include <string>
#include <sstream>
#include <stdexcept>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    if (domain.empty()) {
        throw std::invalid_argument("Domain cannot be empty.");
    }

    std::string url = "https://";
    
    // Check if the subdomain prefix is valid
    if (!subdomain_prefix.empty()) {
        // Handle case where subdomain might be a full domain
        if (subdomain_prefix.find('.') != std::string::npos) {
            url += subdomain_prefix;
        } else {
            url += subdomain_prefix + "." + domain;
        }
    } else {
        // If subdomain is empty or invalid, use the domain itself
        url += domain;
    }

    return url;
}