#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 빈 도메인인 경우 빈 문자열 반환
    if (domain.empty()) {
        return "";
    }
    
    // 하위 도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    bool is_valid = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
    });
    
    // 유효하지 않은 경우 도메인 자체 반환
    if (!is_valid) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사가 점으로 시작하거나 끝나지 않는지 확인
    if (subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.') {
        return "https://" + domain;
    }
    
    // 연속된 점이 없는지 확인
    if (subdomain_prefix.find("..") != std::string::npos) {
        return "https://" + domain;
    }
    
    // 모든 검사를 통과한 경우 하위 도메인 접두사와 도메인 결합
    return "https://" + subdomain_prefix + "." + domain;
}