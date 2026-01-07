#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 결과 URL을 구성할 문자열
    std::string result = "https://";
    
    // 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체를 반환
    if (subdomain_prefix.empty()) {
        result += domain;
        return result;
    }
    
    // 서브도메인 접두사에서 선행/후행 공백 제거
    std::string trimmed_prefix = subdomain_prefix;
    
    // 선행 공백 제거
    size_t start = trimmed_prefix.find_first_not_of(" \t\n\r");
    if (start != std::string::npos) {
        trimmed_prefix = trimmed_prefix.substr(start);
    } else {
        // 모든 문자가 공백인 경우
        trimmed_prefix.clear();
    }
    
    // 후행 공백 제거
    size_t end = trimmed_prefix.find_last_not_of(" \t\n\r");
    if (end != std::string::npos) {
        trimmed_prefix = trimmed_prefix.substr(0, end + 1);
    }
    
    // 공백 제거 후 비어있는지 확인
    if (trimmed_prefix.empty()) {
        result += domain;
        return result;
    }
    
    // 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    bool is_valid = true;
    for (char c : trimmed_prefix) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            is_valid = false;
            break;
        }
    }
    
    // 점으로 시작하거나 끝나는지 확인
    if (is_valid && (trimmed_prefix.front() == '.' || trimmed_prefix.back() == '.')) {
        is_valid = false;
    }
    
    // 연속된 점이 있는지 확인
    if (is_valid && trimmed_prefix.find("..") != std::string::npos) {
        is_valid = false;
    }
    
    // 유효하지 않은 경우 도메인 자체를 반환
    if (!is_valid) {
        result += domain;
        return result;
    }
    
    // 유효한 서브도메인 접두사인 경우 URL 구성
    result += trimmed_prefix + "." + domain;
    return result;
}