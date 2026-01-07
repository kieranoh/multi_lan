#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target URL starts with "https://"
    const std::string httpsPrefix = "https://";
    if (target.compare(0, httpsPrefix.size(), httpsPrefix) != 0) {
        return "Invalid URL: must start with https://"; // Handle invalid URLs
    }
    
    // Build the domain URL for comparison
    std::string domainUrl = httpsPrefix + domain;

    // Check if the target URL starts with the domain URL
    if (target.find(domainUrl) == 0) {
        // Target URL is within the provided domain
        return target;
    } else {
        // Redirect to the domain URL
        return domainUrl;
    }
}