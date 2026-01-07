#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 검증
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }

    // 정규 표현식으로 URL 파싱
    std::regex url_regex(R"(^(https?):\/\/([^\/:]+)(?::(\d+))?(\/.*)?$)", std::regex::icase);
    std::smatch url_match;
    
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효한 URL 형식이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // 호스트명 추출 (그룹 2)
    std::string hostname = url_match[2].str();
    
    // 도메인 일치 확인
    // 호스트명이 도메인으로 끝나거나 정확히 일치하는지 확인
    bool is_within_domain = false;
    
    if (hostname == domain) {
        is_within_domain = true;
    } else if (hostname.length() > domain.length() + 1) {
        // 서브도메인 확인: ".domain"으로 끝나는지 확인
        if (hostname[hostname.length() - domain.length() - 1] == '.' &&
            hostname.substr(hostname.length() - domain.length()) == domain) {
            is_within_domain = true;
        }
    }
    
    // 도메인 내에 있으면 원래 URL을 https로 반환
    if (is_within_domain) {
        // 프로토콜을 https로 강제
        std::string path = url_match[4].matched ? url_match[4].str() : "/";
        return "https://" + hostname + path;
    } else {
        // 도메인 외부면 도메인 URL로 리디렉션
        return "https://" + domain;
    }
}