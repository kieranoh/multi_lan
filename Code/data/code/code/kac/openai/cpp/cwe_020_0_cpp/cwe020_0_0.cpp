#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target URL starts with "https://"
    const std::string protocol = "https://";
    if (target.substr(0, protocol.length()) != protocol) {
        return "https://" + domain; // Ensure using HTTPS
    }

    // Extract the host from the target URL
    std::string host;
    std::size_t start = protocol.length();
    std::size_t end = target.find('/', start);
    if (end == std::string::npos) {
        host = target.substr(start);
    } else {
        host = target.substr(start, end - start);
    }

    // Check if the host ends with the domain
    if (host.find(domain) != std::string::npos) {
        return target; // Return the original target URL
    } else {
        return "https://" + domain; // Redirect to the domain URL
    }
}