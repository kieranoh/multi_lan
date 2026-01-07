#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 정규 표현식 패턴
    std::string pattern = R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // 정규 표현식 객체 생성
    std::regex email_regex(pattern);
    
    // 이메일이 패턴과 일치하는지 확인
    bool is_valid = std::regex_match(email, email_regex);
    
    // 추가 검증: 로컬 파트와 도메인 파트 길이 확인
    if (is_valid) {
        size_t at_pos = email.find('@');
        if (at_pos != std::string::npos) {
            std::string local_part = email.substr(0, at_pos);
            std::string domain_part = email.substr(at_pos + 1);
            
            // 로컬 파트는 최대 64자, 도메인 파트는 최대 255자
            if (local_part.length() > 64 || domain_part.length() > 255) {
                is_valid = false;
            }
            
            // 도메인 파트에 연속된 점이 있는지 확인
            if (domain_part.find("..") != std::string::npos) {
                is_valid = false;
            }
            
            // 도메인 파트의 각 레이블이 1-63자 사이인지 확인
            size_t start = 0;
            size_t dot_pos;
            do {
                dot_pos = domain_part.find('.', start);
                std::string label = domain_part.substr(start, dot_pos - start);
                if (label.length() < 1 || label.length() > 63) {
                    is_valid = false;
                    break;
                }
                start = dot_pos + 1;
            } while (dot_pos != std::string::npos);
        }
    }
    
    return std::make_tuple(is_valid, pattern);
}