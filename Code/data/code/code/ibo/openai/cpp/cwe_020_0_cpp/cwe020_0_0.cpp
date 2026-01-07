#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::regex domain_regex("^(https?://)?(www\\.)?(" + domain + ")(/.*)?$");
    if (std::regex_match(target, domain_regex)) {
        return target;
    } else {
        return "https://" + domain;
    }
}