#include <string>
#include <cctype>
#include <algorithm>

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
    // 1. 공백만 있는지 확인
    bool all_spaces = true;
    for (char c : subdomain_prefix) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            all_spaces = false;
            break;
        }
    }
    if (all_spaces) {
        return "https://" + domain;
    }
    
    // 2. 유효한 문자만 포함하는지 확인 (알파벳, 숫자, 점, 하이픈)
    //    점이나 하이픈으로 시작하거나 끝나지 않아야 함
    bool valid = true;
    for (size_t i = 0; i < subdomain_prefix.length(); ++i) {
        char c = subdomain_prefix[i];
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-')) {
            valid = false;
            break;
        }
        // 점이나 하이픈으로 시작하거나 끝나는 경우
        if ((c == '.' || c == '-') && (i == 0 || i == subdomain_prefix.length() - 1)) {
            valid = false;
            break;
        }
        // 연속된 점이나 하이픈 확인
        if ((c == '.' || c == '-') && i > 0 && 
            (subdomain_prefix[i-1] == '.' || subdomain_prefix[i-1] == '-')) {
            valid = false;
            break;
        }
    }
    
    if (!valid) {
        return "https://" + domain;
    }
    
    // 유효한 하위 도메인 접두사인 경우 URL 생성
    return "https://" + subdomain_prefix + "." + domain;
}