#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::regex domain_pattern("^(https://)?([a-zA-Z0-9-]+\\.)*" + domain + "(/.*)?$");
    if (std::regex_match(target, domain_pattern)) {
        return target;
    } else {
        return "https://" + domain;
    }
}