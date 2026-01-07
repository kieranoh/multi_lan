#include <string>
#include <cctype>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // If target doesn't start with https://, return domain with https://
        return https_prefix + domain;
    }
    
    // Extract the host part from the target URL
    // Start after "https://" (8 characters)
    size_t host_start = https_prefix.length();
    size_t host_end = target.find('/', host_start);
    
    std::string target_host;
    if (host_end == std::string::npos) {
        target_host = target.substr(host_start);
    } else {
        target_host = target.substr(host_start, host_end - host_start);
    }
    
    // Check if target_host ends with domain
    // First, check if target_host is exactly equal to domain
    if (target_host == domain) {
        return target;
    }
    
    // Check if target_host ends with "." + domain
    // and ensure it's a proper subdomain (not just a suffix match)
    std::string domain_with_dot = "." + domain;
    if (target_host.length() > domain_with_dot.length() &&
        target_host.substr(target_host.length() - domain_with_dot.length()) == domain_with_dot) {
        // Verify it's a valid subdomain by checking the character before the dot
        size_t dot_pos = target_host.length() - domain_with_dot.length();
        if (dot_pos > 0) {
            return target;
        }
    }
    
    // If target_host doesn't match domain or end with .domain, return domain URL
    return https_prefix + domain;
}