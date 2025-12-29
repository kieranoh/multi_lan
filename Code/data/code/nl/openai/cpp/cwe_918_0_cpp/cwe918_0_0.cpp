#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Regex om een geldig subdomein te controleren
    std::regex subdomain_regex("^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\\.[A-Za-z0-9-]{1,63})*$");

    // Controleer of de subdomain_prefix geldig is
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain;
    }

    return "https://" + subdomain_prefix + "." + domain;
}