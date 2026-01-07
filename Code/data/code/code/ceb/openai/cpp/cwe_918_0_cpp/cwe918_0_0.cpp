#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Check if the subdomain_prefix is valid using a regex pattern
    std::regex subdomain_pattern("^(?!-)[A-Za-z0-9-]{1,63}(?<!-)$");
    std::string url;

    // If the subdomain_prefix is empty or does not match the pattern, return the domain itself
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_pattern)) {
        url = "https://" + domain;
    } else {
        url = "https://" + subdomain_prefix + "." + domain;
    }

    return url;
}