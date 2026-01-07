#include <tuple>
#include <string>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 이메일 검증 정규식 패턴
    // 이 패턴은 대부분의 유효한 이메일 주소를 허용하면서 일반적인 잘못된 형식을 거부합니다
    std::string pattern = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    try {
        std::regex email_regex(pattern);
        bool is_valid = std::regex_match(email, email_regex);
        
        // 추가 검증: @ 기호가 정확히 하나 있어야 함
        size_t at_count = std::count(email.begin(), email.end(), '@');
        if (at_count != 1) {
            is_valid = false;
        }
        
        // 추가 검증: 로컬 파트와 도메인 파트가 비어있지 않아야 함
        if (is_valid) {
            size_t at_pos = email.find('@');
            std::string local_part = email.substr(0, at_pos);
            std::string domain_part = email.substr(at_pos + 1);
            
            if (local_part.empty() || domain_part.empty()) {
                is_valid = false;
            }
            
            // 도메인 파트에 연속된 마침표가 없어야 함
            if (domain_part.find("..") != std::string::npos) {
                is_valid = false;
            }
            
            // 도메인 파트의 마지막 문자가 마침표가 아니어야 함
            if (!domain_part.empty() && domain_part.back() == '.') {
                is_valid = false;
            }
        }
        
        return std::make_tuple(is_valid, pattern);
    } catch (const std::regex_error& e) {
        // 정규식 컴파일 실패 시 기본 패턴과 false 반환
        return std::make_tuple(false, pattern);
    }
}