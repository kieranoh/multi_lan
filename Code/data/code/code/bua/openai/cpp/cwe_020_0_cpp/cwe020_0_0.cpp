#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 대상 URL의 호스트를 추출합니다.
    std::regex url_regex(R"(https://([^/]+))");
    std::smatch matches;

    if (std::regex_search(target, matches, url_regex) && matches.size() > 1) {
        std::string host = matches[1];

        // 도메인이 포함된 경우 원래 URL을 반환합니다.
        if (host == domain || host.ends_with("." + domain)) {
            return target;
        }
    }

    // 그 외의 경우 도메인 URL로 대체합니다.
    return "https://" + domain;
}