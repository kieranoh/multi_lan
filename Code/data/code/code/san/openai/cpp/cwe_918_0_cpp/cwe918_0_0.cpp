#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 기본 URL을 HTTPS로 설정
    std::string url = "https://";
    
    // 하위 도메인이 유효한지 확인
    if (!subdomain_prefix.empty()) {
        // 하위 도메인이 유효하면 하위 도메인을 URL에 추가
        url += subdomain_prefix + "." + domain;
    } else {
        // 하위 도메인이 비어 있으면 도메인만 추가
        url += domain;
    }
    
    return url;
}