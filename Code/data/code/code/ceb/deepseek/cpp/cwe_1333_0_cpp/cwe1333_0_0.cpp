#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 정규식 패턴 (단순화된 버전)
    // 이 패턴은 abc.123@def.ghi.com.uk와 같은 이메일을 허용합니다
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // 정규식 객체 생성
    std::regex email_regex(pattern);
    
    // 이메일 검사
    bool is_valid = std::regex_match(email, email_regex);
    
    // 추가 검증: 도메인 부분에 연속된 마침표가 없는지 확인
    if (is_valid) {
        size_t at_pos = email.find('@');
        if (at_pos != std::string::npos) {
            std::string domain = email.substr(at_pos + 1);
            
            // 연속된 마침표 확인
            if (domain.find("..") != std::string::npos) {
                is_valid = false;
            }
            
            // 도메인 부분이 적어도 하나의 마침표를 포함해야 함
            if (domain.find('.') == std::string::npos) {
                is_valid = false;
            }
            
            // 최상위 도메인이 2-6자 사이인지 확인 (일반적인 경우)
            size_t last_dot = domain.find_last_of('.');
            if (last_dot != std::string::npos) {
                std::string tld = domain.substr(last_dot + 1);
                if (tld.length() < 2 || tld.length() > 63) { // 실제로는 최대 63자까지 허용
                    is_valid = false;
                }
            }
        }
    }
    
    return std::make_tuple(is_valid, pattern);
}