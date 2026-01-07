#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if target starts with "https://"
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // If target doesn't start with https://, return domain with https://
        return https_prefix + domain;
    }
    
    // Extract the host part from the target URL
    // Remove "https://" prefix
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // Find the first '/' to separate host from path
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_host;
    
    if (slash_pos == std::string::npos) {
        // No path, entire string is host
        target_host = target_without_protocol;
    } else {
        // Extract host part
        target_host = target_without_protocol.substr(0, slash_pos);
    }
    
    // Check if target_host ends with the domain
    // First check if target_host is exactly equal to domain
    if (target_host == domain) {
        return target;
    }
    
    // Check if target_host ends with "." + domain
    std::string domain_with_dot = "." + domain;
    if (target_host.length() > domain_with_dot.length() && 
        target_host.substr(target_host.length() - domain_with_dot.length()) == domain_with_dot) {
        return target;
    }
    
    // If we get here, target is not within the domain
    return https_prefix + domain;
}