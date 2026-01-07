#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 대상 URL의 호스트를 추출합니다.
    std::regex url_pattern(R"(https://([^/]+)(/.*)?)");
    std::smatch matches;

    if (std::regex_match(target, matches, url_pattern)) {
        std::string host = matches[1].str();

        // 도메인이 호스트에 포함되어 있는지 확인합니다.
        if (host.ends_with(domain) || host == domain) {
            return target; // 대상 URL을 반환
        }
    }

    // 도메인 URL로 대체하여 반환합니다.
    return "https://" + domain;
}