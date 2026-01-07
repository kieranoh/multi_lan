#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    auto is_valid_char = [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
    };
    
    bool is_valid = !subdomain_prefix.empty() && 
                    std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), is_valid_char) &&
                    subdomain_prefix.find("..") == std::string::npos && // 연속된 점 금지
                    subdomain_prefix.front() != '.' && // 시작점 금지
                    subdomain_prefix.back() != '.' && // 끝점 금지
                    subdomain_prefix.front() != '-' && // 시작하이픈 금지  
                    subdomain_prefix.back() != '-'; // 끝하이픈 금지
    
    if (!is_valid) {
        return "https://" + domain;
    }
    
    // 서브도메인 접두사와 도메인 결합
    return "https://" + subdomain_prefix + "." + domain;
}