#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::string protocol = "https://";
    std::string domain_with_protocol = protocol + domain;

    // Check if the target URL starts with the correct protocol and contains the domain
    if (target.find(domain_with_protocol) == 0 || target.find(protocol + "www." + domain) == 0) {
        return target;
    }

    // If not, return the domain URL with HTTPS protocol
    return domain_with_protocol;
}