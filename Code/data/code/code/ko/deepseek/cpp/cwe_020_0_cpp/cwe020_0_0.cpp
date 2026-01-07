#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // URL 파싱을 위한 정규식 패턴
    std::regex url_pattern(R"(^(https?)://([^/?#]+)([^?#]*)(\?[^#]*)?(#.*)?$)");
    std::smatch url_match;
    
    // 대상 URL이 유효한 URL 형식인지 확인
    if (!std::regex_match(target, url_match, url_pattern)) {
        throw std::invalid_argument("Invalid target URL format");
    }

    // 프로토콜과 호스트 추출
    std::string protocol = url_match[1].str();  // http 또는 https
    std::string host = url_match[2].str();
    std::string path = url_match[3].str();
    std::string query = url_match[4].str();
    std::string fragment = url_match[5].str();

    // 호스트가 도메인 내에 있는지 확인
    // 1. 정확히 일치하는 경우
    // 2. 서브도메인인 경우 (예: music.example.com은 example.com의 서브도메인)
    bool is_within_domain = false;
    
    if (host == domain) {
        is_within_domain = true;
    } else if (host.length() > domain.length() + 1) {
        // 서브도메인 확인 (예: music.example.com은 .example.com으로 끝나야 함)
        std::string suffix = "." + domain;
        if (host.length() > suffix.length() && 
            host.substr(host.length() - suffix.length()) == suffix) {
            is_within_domain = true;
        }
    }

    // 도메인 내에 있으면 원래 URL을 https로 반환
    if (is_within_domain) {
        // https 프로토콜 사용 보장
        return "https://" + host + path + query + fragment;
    } else {
        // 도메인 내에 없으면 도메인 URL로 대체
        return "https://" + domain;
    }
}