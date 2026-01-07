#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if subdomain_prefix is empty or invalid
    bool invalid = subdomain_prefix.empty();
    
    // Additional validation: check if subdomain_prefix contains only valid characters
    // Valid characters are alphanumeric, hyphen, and dot (but not at start/end or consecutive dots)
    if (!invalid) {
        // Check for leading/trailing dots or hyphens
        if (subdomain_prefix.front() == '.' || subdomain_prefix.front() == '-' ||
            subdomain_prefix.back() == '.' || subdomain_prefix.back() == '-') {
            invalid = true;
        } else {
            // Check for consecutive dots or invalid characters
            bool has_consecutive_dots = false;
            bool has_invalid_char = false;
            
            for (size_t i = 0; i < subdomain_prefix.length(); ++i) {
                char c = subdomain_prefix[i];
                
                // Check for invalid characters
                if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
                    has_invalid_char = true;
                    break;
                }
                
                // Check for consecutive dots
                if (c == '.' && i > 0 && subdomain_prefix[i-1] == '.') {
                    has_consecutive_dots = true;
                    break;
                }
            }
            
            invalid = has_consecutive_dots || has_invalid_char;
        }
    }
    
    // Construct the URL
    if (invalid) {
        return "https://" + domain;
    } else {
        return "https://" + subdomain_prefix + "." + domain;
    }
}