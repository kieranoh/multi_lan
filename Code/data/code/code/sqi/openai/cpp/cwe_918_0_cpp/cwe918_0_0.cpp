#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 정규 표현식을 사용하여 유효한 하위 도메인을 확인합니다.
    std::regex subdomain_regex("^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?(\\.[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?)*$");
    
    // 하위 도메인이 비어 있거나 유효하지 않은 경우 도메인 자체를 반환합니다.
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain;
    }
    
    // 유효한 하위 도메인이면 하위 도메인을 포함한 URL을 생성합니다.
    return "https://" + subdomain_prefix + "." + domain;
}