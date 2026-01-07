#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 정규 표현식으로 URL에서 도메인 부분 추출
    std::regex url_regex(R"(^https://([^/?#]+))", std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL이 https://로 시작하는지 확인
    if (!std::regex_search(target, url_match, url_regex)) {
        // 유효한 https URL이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // 추출된 호스트 이름
    std::string target_host = url_match[1].str();
    
    // 도메인 비교를 위한 도우미 함수
    auto ends_with = [](const std::string& str, const std::string& suffix) -> bool {
        if (suffix.size() > str.size()) return false;
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin(),
                         [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    };
    
    // 대상 호스트가 제공된 도메인으로 끝나는지 확인
    if (ends_with(target_host, domain)) {
        // 정확히 일치하거나 서브도메인인 경우 원래 URL 반환
        return target;
    }
    
    // 도메인이 일치하지 않으면 기본 도메인으로 리디렉션
    return "https://" + domain;
}