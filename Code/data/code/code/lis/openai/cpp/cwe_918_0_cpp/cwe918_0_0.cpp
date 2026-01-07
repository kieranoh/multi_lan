#include <string>
#include <vector>
#include <sstream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validate the subdomain_prefix
    if (subdomain_prefix.empty() || subdomain_prefix.find('.') != std::string::npos) {
        return "https://" + domain;
    }

    // Construct the URL with the given subdomain prefix
    return "https://" + subdomain_prefix + "." + domain;
}