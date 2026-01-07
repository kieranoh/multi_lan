#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 유효한 서브도메인 이름의 정규 표현식
    const std::string valid_subdomain_pattern = "^[a-zA-Z0-9]([-a-zA-Z0-9]*[a-zA-Z0-9])?$";
    
    // 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체를 반환
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, std::regex(valid_subdomain_pattern))) {
        return "https://" + domain;
    }
    
    // 점이 포함된 서브도메인을 포함한 전체 URL 생성
    return "https://" + subdomain_prefix + "." + domain;
}