#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::regex url_regex(R"(https:\/\/([^\/]+)(\/.*)?)");
    std::smatch match;

    if (std::regex_search(target, match, url_regex)) {
        std::string target_domain = match[1];
        if (target_domain == domain || target_domain.ends_with("." + domain)) {
            return target;
        }
    }
    
    return "https://" + domain;
}