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
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)?)");
    std::smatch url_match;
    
    // 대상 URL이 유효한 URL 형식인지 확인
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효한 URL이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // 프로토콜과 호스트 추출
    std::string protocol = url_match[1].str();
    std::string host = url_match[2].str();
    
    // 호스트가 도메인 내에 있는지 확인
    // 1. 정확히 일치하는 경우
    // 2. 서브도메인인 경우 (예: music.example.com은 example.com의 서브도메인)
    bool is_within_domain = false;
    
    // 정확히 일치하는 경우
    if (host == domain) {
        is_within_domain = true;
    }
    // 서브도메인인 경우 확인
    else if (host.length() > domain.length() + 1) {
        // 호스트가 도메인으로 끝나고 바로 앞에 점(.)이 있는지 확인
        size_t pos = host.length() - domain.length() - 1;
        if (host[pos] == '.' && host.substr(pos + 1) == domain) {
            is_within_domain = true;
        }
    }
    
    // 도메인 내에 있으면 원래 URL을 https로 반환
    if (is_within_domain) {
        // 프로토콜을 https로 강제
        return "https://" + host + url_match[3].str();
    }
    
    // 도메인 내에 없으면 도메인 URL로 리디렉션
    return "https://" + domain;
}