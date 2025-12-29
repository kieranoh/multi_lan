#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Helper function to extract host from URL
    auto extract_host = [](const std::string& url) -> std::string {
        // Find the protocol separator
        size_t protocol_pos = url.find("://");
        if (protocol_pos == std::string::npos) {
            return ""; // Invalid URL format
        }
        
        // Find the start of host (after protocol://)
        size_t host_start = protocol_pos + 3;
        
        // Find the end of host (before path, port, or query)
        size_t host_end = url.find('/', host_start);
        if (host_end == std::string::npos) {
            host_end = url.length();
        }
        
        // Extract host
        std::string host = url.substr(host_start, host_end - host_start);
        
        // Remove port if present
        size_t port_pos = host.find(':');
        if (port_pos != std::string::npos) {
            host = host.substr(0, port_pos);
        }
        
        return host;
    };
    
    // Helper function to check if host ends with domain
    auto host_ends_with_domain = [](const std::string& host, const std::string& domain) -> bool {
        if (domain.empty() || host.empty()) {
            return false;
        }
        
        // Case 1: Exact match
        if (host == domain) {
            return true;
        }
        
        // Case 2: Host ends with .domain
        if (host.length() > domain.length() + 1) {
            if (host[host.length() - domain.length() - 1] == '.' &&
                host.substr(host.length() - domain.length()) == domain) {
                return true;
            }
        }
        
        return false;
    };
    
    // Extract host from target URL
    std::string target_host = extract_host(target);
    
    // Check if target_host ends with the provided domain
    if (!target_host.empty() && host_ends_with_domain(target_host, domain)) {
        return target; // Target is within domain
    }
    
    // Fallback: return https://domain
    return "https://" + domain;
}