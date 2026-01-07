#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.substr(0, https_prefix.size()) != https_prefix) {
        return "Invalid URL: Must use HTTPS protocol.";
    }

    // Extract the host from the target URL
    std::size_t start = https_prefix.size();
    std::size_t end = target.find('/', start);
    std::string host = (end == std::string::npos) ? target.substr(start) : target.substr(start, end - start);

    // Check if the host ends with the specified domain
    if (host == domain || host.size() > domain.size() && host.substr(host.size() - domain.size()) == domain) {
        return target; // The target URL is within the domain
    } else {
        return https_prefix + domain; // Replace with domain URL
    }
}