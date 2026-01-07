#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 정규 표현식을 사용하여 유효한 하위 도메인 패턴 검사
    std::regex subdomain_pattern(R"(^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?$)");
    
    // 하위 도메인이 유효하다면 URL을 생성하고, 그렇지 않다면 도메인만 반환
    if (!subdomain_prefix.empty() && std::regex_match(subdomain_prefix, subdomain_pattern)) {
        return "https://" + subdomain_prefix + "." + domain;
    }
    
    return "https://" + domain;
}