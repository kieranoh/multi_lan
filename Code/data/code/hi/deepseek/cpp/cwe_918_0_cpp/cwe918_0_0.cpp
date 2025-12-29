#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if subdomain_prefix is empty or invalid
    bool valid_subdomain = false;
    if (!subdomain_prefix.empty()) {
        // Check if subdomain_prefix contains at least one alphanumeric character
        valid_subdomain = std::any_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                      [](char c) { return std::isalnum(static_cast<unsigned char>(c)); });
    }
    
    std::string result = "https://";
    
    if (valid_subdomain) {
        // Add subdomain prefix
        result += subdomain_prefix;
        // Add dot separator if subdomain doesn't already end with dot
        if (!subdomain_prefix.empty() && subdomain_prefix.back() != '.') {
            result += '.';
        }
    }
    
    // Add domain
    result += domain;
    
    return result;
}