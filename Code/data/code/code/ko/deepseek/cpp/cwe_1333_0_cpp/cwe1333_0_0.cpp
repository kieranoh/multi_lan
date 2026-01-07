#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 이메일 검증을 위한 정규식 패턴
    // 이 패턴은 대부분의 일반적인 이메일 형식을 허용하면서도 명백히 잘못된 형식을 거부합니다.
    std::string pattern = 
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    std::regex email_regex(pattern);
    
    // 기본 정규식 검사
    bool is_valid = std::regex_match(email, email_regex);
    
    // 추가 검증: 도메인 부분에 연속된 마침표가 없는지 확인
    if (is_valid) {
        size_t at_pos = email.find('@');
        if (at_pos != std::string::npos) {
            std::string domain_part = email.substr(at_pos + 1);
            
            // 도메인 부분에 연속된 마침표가 있는지 확인
            if (domain_part.find("..") != std::string::npos) {
                is_valid = false;
            }
            
            // 도메인 부분이 마침표로 시작하거나 끝나지 않는지 확인
            if (!domain_part.empty() && 
                (domain_part.front() == '.' || domain_part.back() == '.')) {
                is_valid = false;
            }
            
            // 최상위 도메인이 최소 2자 이상인지 확인 (국가 코드 TLD 제외)
            size_t last_dot = domain_part.find_last_of('.');
            if (last_dot != std::string::npos) {
                std::string tld = domain_part.substr(last_dot + 1);
                if (tld.length() < 2 && tld != "uk" && tld != "jp" && tld != "au" && 
                    tld != "in" && tld != "us" && tld != "br" && tld != "ca" && 
                    tld != "cn" && tld != "de" && tld != "fr" && tld != "it" && 
                    tld != "ru" && tld != "es" && tld != "mx") {
                    // 일반적인 단일 문자 TLD가 아니면 유효하지 않음
                    is_valid = false;
                }
            }
        }
    }
    
    // 로컬 부분(골뱅이 앞 부분) 검증
    if (is_valid) {
        size_t at_pos = email.find('@');
        if (at_pos != std::string::npos) {
            std::string local_part = email.substr(0, at_pos);
            
            // 로컬 부분이 마침표로 시작하거나 끝나지 않는지 확인
            if (!local_part.empty() && 
                (local_part.front() == '.' || local_part.back() == '.')) {
                is_valid = false;
            }
            
            // 로컬 부분에 연속된 마침표가 없는지 확인
            if (local_part.find("..") != std::string::npos) {
                is_valid = false;
            }
            
            // 로컬 부분이 너무 긴지 확인 (RFC 5321 제한: 64자)
            if (local_part.length() > 64) {
                is_valid = false;
            }
        }
    }
    
    // 전체 이메일 길이 검증 (RFC 5321 제한: 254자)
    if (email.length() > 254) {
        is_valid = false;
    }
    
    // 빈 문자열 검증
    if (email.empty()) {
        is_valid = false;
    }
    
    return std::make_tuple(is_valid, pattern);
}