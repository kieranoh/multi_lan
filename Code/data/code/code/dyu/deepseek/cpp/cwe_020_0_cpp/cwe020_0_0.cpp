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
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)(\?[^#]*)?(#.*)?$)", 
                        std::regex::icase);
    std::smatch url_match;
    
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효한 URL 형식이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // 프로토콜과 호스트 추출
    std::string protocol = url_match[1].str();
    std::string host = url_match[2].str();
    
    // 호스트가 도메인으로 끝나는지 확인
    // 예: "music.example.com"은 "example.com"으로 끝나야 함
    if (host.length() >= domain.length()) {
        // 정확히 일치하거나 서브도메인인 경우
        if (host == domain || 
            (host.length() > domain.length() && 
             host[host.length() - domain.length() - 1] == '.' &&
             host.substr(host.length() - domain.length()) == domain)) {
            
            // 경로와 쿼리, 프래그먼트 재구성
            std::string path = url_match[3].str();
            std::string query = url_match[4].str();
            std::string fragment = url_match[5].str();
            
            // 항상 https 프로토콜 사용
            return "https://" + host + path + query + fragment;
        }
    }
    
    // 도메인 내에 없으면 도메인으로 리디렉션
    return "https://" + domain;
}