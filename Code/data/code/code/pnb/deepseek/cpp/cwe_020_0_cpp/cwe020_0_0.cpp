#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // If target doesn't start with https://, return domain with https://
        return https_prefix + domain;
    }
    
    // Extract the host part from the target URL
    // Find the position after "https://"
    size_t host_start = https_prefix.length();
    size_t host_end = target.find('/', host_start);
    
    std::string target_host;
    if (host_end == std::string::npos) {
        // No path after host
        target_host = target.substr(host_start);
    } else {
        // Extract host part
        target_host = target.substr(host_start, host_end - host_start);
    }
    
    // Check if target_host ends with domain
    // First, check if target_host is exactly equal to domain
    if (target_host == domain) {
        return target;
    }
    
    // Check if target_host ends with "." + domain
    if (target_host.length() > domain.length() + 1) {
        size_t dot_pos = target_host.length() - domain.length() - 1;
        if (target_host[dot_pos] == '.' && 
            target_host.substr(dot_pos + 1) == domain) {
            return target;
        }
    }
    
    // If target_host doesn't match domain, return https:// + domain
    return https_prefix + domain;
}