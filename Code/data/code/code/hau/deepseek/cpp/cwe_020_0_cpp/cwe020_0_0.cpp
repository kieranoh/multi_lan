#include <string>
#include <cctype>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 1. Check if target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // If target doesn't start with https://, return domain with https://
        return https_prefix + domain;
    }
    
    // 2. Extract the host from target URL (after https:// and before first '/')
    std::string target_host;
    size_t host_start = https_prefix.length();
    size_t host_end = target.find('/', host_start);
    
    if (host_end == std::string::npos) {
        target_host = target.substr(host_start);
    } else {
        target_host = target.substr(host_start, host_end - host_start);
    }
    
    // 3. Check if target_host ends with domain
    // Case-insensitive comparison for domain matching
    if (target_host.length() >= domain.length()) {
        // Extract the ending part of target_host with same length as domain
        std::string target_end = target_host.substr(target_host.length() - domain.length());
        
        // Convert both to lowercase for case-insensitive comparison
        std::string target_end_lower = target_end;
        std::string domain_lower = domain;
        std::transform(target_end_lower.begin(), target_end_lower.end(), target_end_lower.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        std::transform(domain_lower.begin(), domain_lower.end(), domain_lower.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        // Check if target ends with domain
        if (target_end_lower == domain_lower) {
            // Additional check: make sure it's not just a partial match
            // If target_host is longer than domain, the character before domain must be '.'
            if (target_host.length() == domain.length() || 
                target_host[target_host.length() - domain.length() - 1] == '.') {
                return target; // Valid subdomain or exact match
            }
        }
    }
    
    // 4. If not in domain, return domain URL with https://
    return https_prefix + domain;
}