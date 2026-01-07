#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 정규 표현식 패턴
    // 이 패턴은 대부분의 유효한 이메일 주소를 인식하면서도 일반적인 잘못된 형식을 거부합니다
    std::string pattern = 
        R"(^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    // 추가 검증: 이메일 길이 제한 (RFC 5321 기준)
    if (email.empty() || email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // 로컬 파트와 도메인 파트 분리
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 길이 검증 (RFC 5321 기준: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인 파트 검증
    if (domain_part.empty() || domain_part.length() > 253) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인에 연속된 마침표 금지
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인 파트의 각 레이블 검증 (최대 63자)
    size_t start = 0;
    size_t dot_pos;
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain_part.substr(start) : 
                           domain_part.substr(start, dot_pos - start);
        
        if (label.empty() || label.length() > 63) {
            return std::make_tuple(false, pattern);
        }
        
        // 레이블 시작과 끝이 하이픈이면 안됨
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 정규 표현식으로 최종 검증
    try {
        std::regex email_regex(pattern);
        bool is_valid = std::regex_match(email, email_regex);
        return std::make_tuple(is_valid, pattern);
    } catch (const std::regex_error& e) {
        // 정규 표현식 오류 발생 시 기본 패턴 반환
        return std::make_tuple(false, pattern);
    }
}