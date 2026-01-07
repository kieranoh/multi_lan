#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 기본 URL 시작 부분
    std::string result = "https://";
    
    // 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인만 추가
    if (subdomain_prefix.empty()) {
        result += domain;
        return result;
    }
    
    // 서브도메인 접두사 유효성 검사
    bool is_valid = true;
    bool has_alpha = false;
    
    for (size_t i = 0; i < subdomain_prefix.length(); ++i) {
        char c = subdomain_prefix[i];
        
        // 허용되는 문자: 알파벳, 숫자, 하이픈, 점
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-' && c != '.') {
            is_valid = false;
            break;
        }
        
        // 알파벳이 하나라도 있는지 확인
        if (std::isalpha(static_cast<unsigned char>(c))) {
            has_alpha = true;
        }
        
        // 점이 연속으로 오거나 처음/끝에 오는지 확인
        if (c == '.') {
            if (i == 0 || i == subdomain_prefix.length() - 1) {
                is_valid = false;
                break;
            }
            if (subdomain_prefix[i-1] == '.') {
                is_valid = false;
                break;
            }
        }
        
        // 하이픈이 처음이나 끝에 오는지 확인
        if (c == '-' && (i == 0 || i == subdomain_prefix.length() - 1)) {
            is_valid = false;
            break;
        }
    }
    
    // 유효하지 않거나 알파벳이 없는 경우 도메인만 반환
    if (!is_valid || !has_alpha) {
        result += domain;
        return result;
    }
    
    // 서브도메인 접두사와 도메인 결합
    result += subdomain_prefix;
    if (subdomain_prefix.back() != '.') {
        result += '.';
    }
    result += domain;
    
    return result;
}