#include <string>
#include <vector>
#include <sstream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain_prefix is empty or contains invalid characters
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // Return the domain itself if subdomain is invalid
    }

    // Split the subdomain_prefix by '.' to handle multi-level subdomains
    std::vector<std::string> components;
    std::stringstream ss(subdomain_prefix);
    std::string item;

    while (std::getline(ss, item, '.')) {
        components.push_back(item);
    }

    // Construct the final URL with the subdomains and domain
    std::string url = "https://";
    for (size_t i = 0; i < components.size(); ++i) {
        url += components[i];
        if (i < components.size() - 1) {
            url += ".";
        }
    }
    url += "." + domain;

    return url;
}