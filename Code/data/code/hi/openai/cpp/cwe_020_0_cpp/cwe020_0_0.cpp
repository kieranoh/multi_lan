#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Define the HTTPS prefix
    const std::string https_prefix = "https://";
    
    // Check if the target URL starts with the HTTPS prefix
    if (target.substr(0, https_prefix.length()) != https_prefix) {
        return https_prefix + domain; // Return domain with HTTPS if target does not use HTTPS
    }

    // Extract the domain part from the target URL
    std::size_t domain_start = target.find("://") + 3; // Move past the "://"
    std::size_t domain_end = target.find('/', domain_start);
    std::string target_domain = target.substr(domain_start, domain_end - domain_start);
    
    // Check if the target domain matches the given domain
    if (target_domain == domain || target_domain.ends_with("." + domain)) {
        return target; // Return the target URL if it matches the domain
    } else {
        return https_prefix + domain; // Otherwise, return the domain with HTTPS
    }
}