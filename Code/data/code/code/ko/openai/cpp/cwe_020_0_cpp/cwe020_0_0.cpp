#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 주어진 도메인과 일치하는지 확인
    std::regex domain_regex("https?://([^/]+)");
    std::smatch match;

    // 대상 URL에서 호스트를 추출
    if (std::regex_search(target, match, domain_regex)) {
        std::string host = match[1];

        // 호스트가 지정된 도메인을 포함하는지 확인
        if (host.find(domain) != std::string::npos) {
            return target; // 도메인 내에 있는 경우, 원래 URL 반환
        }
    }

    // 기본 도메인 URL로 리디렉션
    return "https://" + domain;
}