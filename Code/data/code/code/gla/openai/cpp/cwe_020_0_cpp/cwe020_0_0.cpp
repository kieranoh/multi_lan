#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 URL에서 프로토콜 및 도메인을 확인합니다.
    std::regex url_regex(R"(https:\/\/([a-zA-Z0-9\-\.]+)(\/.*)?$)");
    std::smatch match;

    // 정규 표현식을 사용하여 target URL을 매칭합니다.
    if (std::regex_match(target, match, url_regex)) {
        // 매칭된 도메인을 확인합니다.
        std::string matched_domain = match[1].str();
        if (matched_domain.find(domain) != std::string::npos) {
            // 주어진 도메인 내에 있으면 target URL을 반환합니다.
            return target;
        }
    }
    // 그렇지 않으면 도메인 URL로 리디렉션을 반환합니다.
    return "https://" + domain;
}