#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    bool valid = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
    });
    
    // 유효하지 않거나 점으로 시작하거나 끝나는 경우 도메인 자체 반환
    if (!valid || subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.') {
        return "https://" + domain;
    }
    
    // 연속된 점이 있는지 확인
    if (subdomain_prefix.find("..") != std::string::npos) {
        return "https://" + domain;
    }
    
    // 유효한 서브도메인 접두사인 경우 전체 URL 구성
    return "https://" + subdomain_prefix + "." + domain;
}