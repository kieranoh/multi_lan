#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.substr(0, https_prefix.size()) != https_prefix) {
        return "https://" + domain; // If not, return the domain with HTTPS
    }

    // Extract the host from the target URL
    std::size_t start = https_prefix.size();
    std::size_t end = target.find('/', start);
    std::string host = (end == std::string::npos) ? target.substr(start) : target.substr(start, end - start);

    // Check if the host ends with the domain
    if (host == domain || host.ends_with("." + domain)) {
        return target; // Return the original target if it is within the domain
    } else {
        // Otherwise, return the domain URL
        return "https://" + domain; 
    }
}