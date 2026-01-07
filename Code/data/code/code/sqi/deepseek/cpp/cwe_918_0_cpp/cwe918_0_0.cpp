#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 빈 도메인인 경우 빈 문자열 반환
    if (domain.empty()) {
        return "";
    }
    
    // 하위 도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사에서 선행/후행 공백 제거
    std::string trimmed_subdomain = subdomain_prefix;
    
    // 선행 공백 제거
    trimmed_subdomain.erase(trimmed_subdomain.begin(), 
                          std::find_if(trimmed_subdomain.begin(), trimmed_subdomain.end(),
                                     [](unsigned char ch) { return !std::isspace(ch); }));
    
    // 후행 공백 제거
    trimmed_subdomain.erase(std::find_if(trimmed_subdomain.rbegin(), trimmed_subdomain.rend(),
                                       [](unsigned char ch) { return !std::isspace(ch); }).base(),
                          trimmed_subdomain.end());
    
    // 공백만 있는 경우 도메인 자체 반환
    if (trimmed_subdomain.empty()) {
        return "https://" + domain;
    }
    
    // 하위 도메인 접두사가 유효한 경우 URL 구성
    return "https://" + trimmed_subdomain + "." + domain;
}