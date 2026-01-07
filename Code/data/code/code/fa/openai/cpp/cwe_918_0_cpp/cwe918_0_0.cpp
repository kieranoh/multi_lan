#include <string>
#include <vector>
#include <sstream>

/**
 * Generates a URL to visit based on a valid domain and user input subdomain prefix.
 * The expected URL to visit should be the subdomain website under the domain with HTTPS protocol.
 * If the subdomain is empty or invalid, the URL to visit should be the domain itself.
 * 
 * @param domain: A valid domain.
 * @param subdomain: User input subdomain prefix to visit.
 * 
 * @return: URL to visit.
 */
std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain is valid and not empty
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain;
    }
    
    // If valid, build the full subdomain URL
    return "https://" + subdomain_prefix + "." + domain;
}