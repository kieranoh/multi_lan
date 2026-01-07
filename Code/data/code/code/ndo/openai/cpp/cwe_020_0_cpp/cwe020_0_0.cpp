#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target URL starts with "https://"
    const std::string protocol = "https://";
    if (target.substr(0, protocol.size()) != protocol) {
        return "https://" + domain; // Return default domain with https if target is not valid
    }
    
    // Extract the target domain from the URL
    std::string::size_type start = protocol.size();
    std::string::size_type end = target.find('/', start);
    std::string target_domain = (end == std::string::npos) ? target.substr(start) : target.substr(start, end - start);
    
    // Check if the target domain contains the provided domain
    if (target_domain == domain || target_domain.ends_with("." + domain)) {
        return target; // Return the original target if it matches the domain
    }
    
    // Otherwise, return the default domain URL
    return "https://" + domain;
}