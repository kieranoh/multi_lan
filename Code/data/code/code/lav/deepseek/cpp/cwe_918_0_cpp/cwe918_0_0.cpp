#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    bool valid = true;
    for (char c : subdomain_prefix) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            valid = false;
            break;
        }
    }
    
    // 유효하지 않은 경우 도메인 자체 반환
    if (!valid) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사가 점으로 시작하거나 끝나지 않는지 확인
    if (!subdomain_prefix.empty()) {
        if (subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.') {
            return "https://" + domain;
        }
    }
    
    // 연속된 점이 있는지 확인
    if (subdomain_prefix.find("..") != std::string::npos) {
        return "https://" + domain;
    }
    
    // 빈 레이블(두 점 사이에 아무것도 없음)이 있는지 확인
    bool empty_label = false;
    if (!subdomain_prefix.empty()) {
        size_t pos = 0;
        while (pos < subdomain_prefix.length()) {
            size_t next_dot = subdomain_prefix.find('.', pos);
            if (next_dot == pos) { // 점 바로 다음에 또 다른 점이 있거나 시작이 점인 경우
                empty_label = true;
                break;
            }
            if (next_dot == std::string::npos) {
                // 마지막 레이블 확인
                if (next_dot == pos) {
                    empty_label = true;
                }
                break;
            }
            pos = next_dot + 1;
        }
    }
    
    if (empty_label) {
        return "https://" + domain;
    }
    
    // 모든 검사를 통과한 경우 정상적인 URL 생성
    return "https://" + subdomain_prefix + "." + domain;
}