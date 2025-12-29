#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target starts with "https://"
    const std::string https_prefix = "https://";
    if (target.substr(0, https_prefix.length()) != https_prefix) {
        return "https://" + domain; // Fallback to domain URL
    }

    // Extract the host from the target URL
    std::size_t start_pos = https_prefix.length();
    std::size_t end_pos = target.find('/', start_pos);
    std::string host = (end_pos == std::string::npos) ? target.substr(start_pos) : target.substr(start_pos, end_pos - start_pos);

    // Check if the host ends with the specified domain
    if (host == domain || host.ends_with("." + domain)) {
        return target; // Return the original target URL
    }

    // Fallback to domain URL if host does not match
    return "https://" + domain;
}