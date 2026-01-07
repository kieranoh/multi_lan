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
    
    // 하위 도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    bool valid = true;
    for (char c : subdomain_prefix) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            valid = false;
            break;
        }
    }
    
    // 하위 도메인 접두사가 유효하지 않거나 점으로 시작하거나 끝나는 경우
    if (!valid || subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.' ||
        subdomain_prefix.find("..") != std::string::npos) {
        return "https://" + domain;
    }
    
    // 최종 URL 생성
    return "https://" + subdomain_prefix + "." + domain;
}