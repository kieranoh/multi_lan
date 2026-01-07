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
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)(?:\?([^#]*))?(?:#(.*))?$)", 
                        std::regex::icase);
    std::smatch url_match;
    
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효한 URL이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    std::string protocol = url_match[1].str();
    std::string host = url_match[2].str();
    std::string path = url_match[3].str();
    
    // 호스트가 도메인으로 끝나는지 확인 (서브도메인 포함)
    // 예: "music.example.com"은 "example.com"으로 끝남
    if (host == domain || 
        (host.length() > domain.length() + 1 && 
         host.substr(host.length() - domain.length() - 1) == "." + domain)) {
        // 대상이 도메인 내에 있으면 원래 URL 반환 (항상 https 사용)
        return "https://" + host + path;
    } else {
        // 도메인 외부면 도메인으로 리디렉션
        return "https://" + domain;
    }
}