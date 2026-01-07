#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target URL starts with "https://"
    const std::string https_prefix = "https://";
    if (target.substr(0, https_prefix.size()) != https_prefix) {
        return "https://" + domain; // Return the domain with HTTPS if the target is not valid
    }
    
    // Extract the host from the target URL
    std::size_t host_start = https_prefix.size();
    std::size_t host_end = target.find('/', host_start);
    
    std::string host = (host_end == std::string::npos) ? target.substr(host_start) : target.substr(host_start, host_end - host_start);
    
    // Check if the host contains the given domain
    if (host.find(domain) != std::string::npos) {
        return target; // Return the original target if it matches the domain
    } else {
        return "https://" + domain; // Return the domain URL if it does not match
    }
}