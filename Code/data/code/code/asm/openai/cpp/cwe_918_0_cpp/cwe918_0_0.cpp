#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 기본 URL 형식을 설정합니다.
    std::string url = "https://";

    // 하위 도메인 접두사가 비어 있지 않고 유효한 경우
    if (!subdomain_prefix.empty()) {
        // 하위 도메인이 도메인과 합쳐질 수 있는지 확인합니다.
        url += subdomain_prefix + "."; 
    }

    // 도메인을 추가합니다.
    url += domain;

    return url;
}