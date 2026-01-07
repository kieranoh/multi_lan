#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 빈 도메인인 경우 빈 문자열 반환
    if (domain.empty()) {
        return "";
    }
    
    // 하위 도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사 유효성 검사
    bool has_valid_char = false;
    for (char c : subdomain_prefix) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-') {
            has_valid_char = true;
        }
        // 유효하지 않은 문자가 포함된 경우 도메인 자체 반환
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-')) {
            return "https://" + domain;
        }
    }
    
    // 유효한 문자가 하나도 없는 경우 도메인 자체 반환
    if (!has_valid_char) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사가 '.'으로 시작하거나 끝나는 경우 도메인 자체 반환
    if (subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.') {
        return "https://" + domain;
    }
    
    // 연속된 '.'이 있는 경우 도메인 자체 반환
    if (subdomain_prefix.find("..") != std::string::npos) {
        return "https://" + domain;
    }
    
    // 유효한 하위 도메인 접두사인 경우 URL 생성
    return "https://" + subdomain_prefix + "." + domain;
}