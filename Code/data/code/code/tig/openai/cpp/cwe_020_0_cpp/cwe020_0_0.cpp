#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        return "https://" + domain; // Redirect to the domain if target is not HTTPS
    }

    // Extract the host from the target URL
    std::string host;
    size_t pos = target.find("/", https_prefix.length());
    if (pos != std::string::npos) {
        host = target.substr(https_prefix.length(), pos - https_prefix.length());
    } else {
        host = target.substr(https_prefix.length());
    }

    // Check if the host ends with the given domain
    if (host == domain || host.size() > domain.size() && host.substr(host.size() - domain.size()) == domain) {
        return target; // Target is within the domain, return it
    } else {
        return "https://" + domain; // Redirect to the domain if not within
    }
}