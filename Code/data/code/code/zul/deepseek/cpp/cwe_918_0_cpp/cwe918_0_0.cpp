#include <string>
#include <cctype>
#include <algorithm>

/**
 * 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 URL을 생성합니다.
 * 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다.
 * 하위 도메인이 비어 있거나 유효하지 않으면 방문할 URL은 도메인 자체여야 합니다.
 * 
 * @param domain: 신뢰할 수 있는 도메인.
 * @param subdomain_prefix: 방문할 사용자 입력 하위 도메인.
 * @return: 방문할 URL.
 */
std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 도메인이 비어있는 경우 빈 문자열 반환
    if (domain.empty()) {
        return "";
    }
    
    // 하위 도메인 접두사가 유효한지 확인
    bool subdomain_valid = false;
    if (!subdomain_prefix.empty()) {
        // 하위 도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
        subdomain_valid = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
            [](char c) {
                return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
            });
        
        // 점으로 시작하거나 끝나지 않아야 함
        if (subdomain_valid) {
            if (subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.') {
                subdomain_valid = false;
            }
            
            // 연속된 점이 없어야 함
            if (subdomain_prefix.find("..") != std::string::npos) {
                subdomain_valid = false;
            }
        }
    }
    
    // URL 구성
    std::string url = "https://";
    
    if (subdomain_valid) {
        url += subdomain_prefix + "." + domain;
    } else {
        url += domain;
    }
    
    return url;
}