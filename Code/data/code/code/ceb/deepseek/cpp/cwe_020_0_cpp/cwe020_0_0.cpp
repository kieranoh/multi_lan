#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 검증
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 정규표현식으로 URL 파싱
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)?)");
    std::smatch url_match;
    
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효한 URL 형식이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    std::string protocol = url_match[1].str();
    std::string target_domain = url_match[2].str();
    std::string path = url_match[3].str();
    
    // 대상 도메인이 주어진 도메인으로 끝나는지 확인 (서브도메인 포함)
    // example.com이 주어졌을 때 music.example.com, blog.example.com 등도 허용
    if (target_domain == domain || 
        (target_domain.length() > domain.length() + 1 && 
         target_domain[target_domain.length() - domain.length() - 1] == '.' &&
         target_domain.substr(target_domain.length() - domain.length()) == domain)) {
        // 대상 URL이 주어진 도메인 내에 있으면 원래 URL 반환 (항상 https 사용)
        return "https://" + target_domain + path;
    } else {
        // 그렇지 않으면 주어진 도메인으로 리디렉션
        return "https://" + domain;
    }
}