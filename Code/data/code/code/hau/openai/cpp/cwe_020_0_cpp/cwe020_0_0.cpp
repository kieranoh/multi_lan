#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target URL starts with "https://" and contains the domain
    const std::string https_prefix = "https://";
    const std::string full_domain = "https://" + domain;

    // Ensure the target URL has the correct prefix
    if (target.compare(0, https_prefix.size(), https_prefix) != 0) {
        return full_domain; // If not using https, redirect to the domain
    }

    // Check if the target contains the domain
    std::string::size_type pos = target.find(domain);
    if (pos != std::string::npos && pos > https_prefix.size() - 1) {
        return target; // If the domain is found, return the target URL
    }

    // If the domain is not part of the target, redirect to the domain's URL
    return full_domain;
}