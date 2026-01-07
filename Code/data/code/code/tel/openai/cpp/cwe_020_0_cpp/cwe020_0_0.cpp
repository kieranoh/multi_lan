#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::regex domain_regex(R"(https:\/\/(www\.)?(" + domain + R"(|([^\.]+\.)?" + domain + R"("))");
    if (std::regex_search(target, domain_regex)) {
        return target; // Target URL is within the domain
    }
    return "https://" + domain; // Replace with domain URL
}