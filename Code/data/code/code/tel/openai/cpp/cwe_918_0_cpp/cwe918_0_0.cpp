#include <string>
#include <stdexcept>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validate the domain
    if (domain.empty() || domain.find('.') == std::string::npos) {
        throw std::invalid_argument("Invalid domain provided");
    }
    
    // Construct the base URL
    std::string url = "https://";

    // Check if the subdomain prefix is valid
    if (!subdomain_prefix.empty()) {
        // Add the subdomain prefix, ensuring to handle the case where it contains additional dots
        url += subdomain_prefix + "." + domain;
    } else {
        // If subdomain prefix is empty, use the domain itself
        url += domain;
    }

    return url;
}