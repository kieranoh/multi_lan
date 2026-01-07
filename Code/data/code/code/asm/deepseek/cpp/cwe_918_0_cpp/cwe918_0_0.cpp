#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 빈 도메인인 경우 빈 문자열 반환
    if (domain.empty()) {
        return "";
    }
    
    // 하위 도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    bool is_valid = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
        [](char c) {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
        });
    
    // 유효하지 않은 하위 도메인인 경우 도메인 자체 반환
    if (!is_valid) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사가 점으로 시작하거나 끝나지 않도록 정리
    std::string cleaned_subdomain = subdomain_prefix;
    
    // 앞의 점 제거
    while (!cleaned_subdomain.empty() && cleaned_subdomain.front() == '.') {
        cleaned_subdomain.erase(0, 1);
    }
    
    // 뒤의 점 제거
    while (!cleaned_subdomain.empty() && cleaned_subdomain.back() == '.') {
        cleaned_subdomain.pop_back();
    }
    
    // 정리 후 비어있으면 도메인 자체 반환
    if (cleaned_subdomain.empty()) {
        return "https://" + domain;
    }
    
    // URL 생성
    return "https://" + cleaned_subdomain + "." + domain;
}