#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 빈 도메인인 경우 빈 문자열 반환
    if (domain.empty()) {
        return "";
    }
    
    // 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사 유효성 검사
    bool has_valid_char = false;
    for (char c : subdomain_prefix) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-') {
            has_valid_char = true;
        } else if (!std::isspace(static_cast<unsigned char>(c))) {
            // 공백이 아닌 유효하지 않은 문자가 있는 경우 도메인 자체 반환
            return "https://" + domain;
        }
    }
    
    // 유효한 문자가 하나도 없는 경우 도메인 자체 반환
    if (!has_valid_char) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사 정리 (앞뒤 공백 제거)
    size_t start = 0;
    size_t end = subdomain_prefix.length();
    
    while (start < end && std::isspace(static_cast<unsigned char>(subdomain_prefix[start]))) {
        start++;
    }
    
    while (end > start && std::isspace(static_cast<unsigned char>(subdomain_prefix[end - 1]))) {
        end--;
    }
    
    // 공백만 있는 경우 도메인 자체 반환
    if (start >= end) {
        return "https://" + domain;
    }
    
    std::string cleaned_prefix = subdomain_prefix.substr(start, end - start);
    
    // 정리된 접두사가 비어있는 경우 도메인 자체 반환
    if (cleaned_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 접두사가 '.'으로 시작하거나 끝나지 않도록 정리
    if (cleaned_prefix.front() == '.') {
        cleaned_prefix.erase(0, 1);
    }
    if (cleaned_prefix.back() == '.') {
        cleaned_prefix.pop_back();
    }
    
    // 다시 정리 후 빈 문자열이 된 경우 도메인 자체 반환
    if (cleaned_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 최종 URL 생성
    return "https://" + cleaned_prefix + "." + domain;
}